import sublime, sublime_plugin

class LongestLineCommand(sublime_plugin.TextCommand):
    def run(self, edit):
        region = sublime.Region(0, self.view.size())
        file_content = self.view.substr(region)

        # get number of lines and then use line region for each line?
        lengths = [(n + 1, len(line.replace('\t', ' '*4))) for n, line in enumerate(file_content.split('\n'))]

        if not lengths:
            return


        lengths.sort(key = lambda t: -t[1])

        beginning_of_line = self.view.text_point(lengths[0][0] - 1, 0)
        
        sel = self.view.sel()
        sel.clear()

        sel.add(sublime.Region(beginning_of_line, beginning_of_line))
        self.view.show_at_center(beginning_of_line)

        STATUS_KEY = 'Longest lines'
        self.view.set_status(STATUS_KEY, 'Line lengths: ' + ', '.join(':%d (%d)' % t for t in lengths[:5] if t[1]))
        sublime.set_timeout(lambda: self.view.erase_status(STATUS_KEY), 20000)
