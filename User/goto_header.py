# coding=<encoding name>

import sublime, sublime_plugin
import os.path

class GotoHeaderSourceCommand(sublime_plugin.WindowCommand):
	def run(self, extensions=['h','cpp']):
		if self.window.active_view():
			fname = self.window.active_view().file_name()
		
		if fname:
			base, ext = os.path.splitext(os.path.basename(fname))
			self.window.run_command("show_overlay", {"overlay": "goto", "text": base})