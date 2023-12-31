﻿# coding=utf-8

import sublime, sublime_plugin

class CloseOthersCommand(sublime_plugin.TextCommand):
	def run(self, edit):
		window = self.view.window()
		group_index, view_index = window.get_view_index(self.view)
		window.run_command('close_others_by_index', dict(group=group_index, index=view_index))
