import sublime, sublime_plugin, os, subprocess

class P4EditCommand(sublime_plugin.TextCommand):
	def run(self, edit):
		if not self.view.file_name():
			print('no file!')
			return

		folder_name, file_name = os.path.split(self.view.file_name())

		command = 'p4 edit -c default '+file_name

		p = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=folder_name, shell=True)
		result, err = p.communicate()

		print('p4: ' + str(result))
		self.view.set_status('p4',(result+err).decode('ascii').strip())
		sublime.set_timeout(self.clear,2000)

	def clear(self):
		self.view.erase_status('p4')
