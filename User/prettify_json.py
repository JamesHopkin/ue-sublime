import json
import sublime
import sublime_plugin


def _collapse_container_starts(formatted):
    """Collapse consecutive container openings onto the same line.

    Merges lines like:
        [           →  [ { [
          {
            [
    But NOT after keys:
        "a":        →  "a":
          [              [ {
            {
    """
    lines = formatted.split('\n')
    changed = True
    while changed:
        changed = False
        new_lines = []
        for line in lines:
            if new_lines:
                prev_stripped = new_lines[-1].rstrip()
                curr_stripped = line.lstrip()
                if (curr_stripped[:1] in ('[', '{')
                        and prev_stripped[-1:] in ('[', '{', ',')):
                    new_lines[-1] = prev_stripped + ' ' + curr_stripped
                    changed = True
                    continue
            new_lines.append(line)
        lines = new_lines
    return '\n'.join(lines)


def _format_elm_style(data, sort_keys=False, indent_size=2, current_indent=0):
    """Format JSON with Elm-style leading commas"""
    current = " " * current_indent

    if isinstance(data, dict):
        if not data:
            return "{}"

        lines = []
        keys = sorted(data.keys()) if sort_keys else data.keys()
        for i, key in enumerate(keys):
            value = data[key]
            padding = " " * (indent_size - 1)
            formatted_value = _format_elm_style(value, sort_keys, indent_size, current_indent + indent_size)
            line_start = current + ("{" if i == 0 else ",")

            # If value is multiline (object/array), put it on next line
            if "\n" in formatted_value:
                lines.append("{}{}\"{}\": ".format(line_start, padding, key))
                lines.append(formatted_value)
            else:
                lines.append("{}{}\"{}\": {}".format(line_start, padding, key, formatted_value))
        lines.append(current + "}")
        return "\n".join(lines)

    elif isinstance(data, list):
        if not data:
            return "[]"

        lines = []
        # fix to put strings first if I ever come across mixes
        if sort_keys and not isinstance(data[0], list) and not isinstance(data[0], dict):
            data = sorted(data)
        for i, item in enumerate(data):
            padding = " " * (indent_size - 1)
            formatted_item = _format_elm_style(item, sort_keys, indent_size, current_indent + indent_size)
            line_start = current + ("[" if i == 0 else ",")

            # If item is multiline (object/array), put it on next line
            if "\n" in formatted_item:
                lines.append("{}{}".format(line_start, padding))
                lines.append(formatted_item)
            else:
                lines.append("{}{}{}".format(line_start, padding, formatted_item))
        lines.append(current + "]")
        return "\n".join(lines)

    elif isinstance(data, str):
        return json.dumps(data, ensure_ascii=False)

    elif isinstance(data, bool):
        return "true" if data else "false"

    elif data is None:
        return "null"

    else:
        return json.dumps(data, ensure_ascii=False)


class PrettifyCurrentFileIfJsonCommand(sublime_plugin.TextCommand):
    def run(self, edit, elm_style=False, sort_keys=False):
        view = self.view
        region = sublime.Region(0, view.size())
        text = view.substr(region)

        # Quick exit on empty files
        if not text.strip():
            sublime.status_message("Prettify JSON: file is empty.")
            return

        # Detect indentation preference from the view
        indent_size = int(view.settings().get("tab_size", 2))
        try:
            data = json.loads(text)
        except json.JSONDecodeError as e:
            sublime.status_message("Prettify JSON: not valid JSON (line {}, col {})".format(e.lineno, e.colno))
            print("Prettify JSON: {} (line {}, col {})".format(e.msg, e.lineno, e.colno))
            return

        # try:
        if elm_style:
            pretty = _format_elm_style(data, sort_keys, indent_size)
            if indent_size == 2:
                pretty = _collapse_container_starts(pretty)
            pretty += "\n"
            style_msg = "Elm-style"
        else:
            pretty = json.dumps(
                data,
                indent=indent_size,
                ensure_ascii=False,
                separators=(",", ": ")
            ) + "\n"
            style_msg = "standard"
        # except Exception as e:
        #     sublime.status_message("Prettify JSON: failed to serialize ({})".format(type(e).__name__))
        #     return

        # Replace entire buffer
        view.replace(edit, region, pretty)
        sublime.status_message("Prettify JSON: done ({}, indent = {}, sort_keys = {})".format(style_msg, indent_size, sort_keys))
