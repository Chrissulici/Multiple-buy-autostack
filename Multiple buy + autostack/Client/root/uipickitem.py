import wndMgr
import work as ui
import ime
import localeInfo
import re

class PickItemDialog(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)

		self.unitValue = 1
		self.maxValue = 0
		self.eventAccept = 0

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def LoadDialog(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "UIScript/pickitemdialog.py")
		except:
			import exception
			exception.Abort("PickItemDialog.LoadDialog.LoadScript")

		try:
			self.board = self.GetChild("board")
			self.maxValueTextLine = self.GetChild("max_value")
			self.pickValueEditLine = self.GetChild("money_value")
			self.acceptButton = self.GetChild("accept_button")
			self.cancelButton = self.GetChild("cancel_button")
		except:
			import exception
			exception.Abort("PickItemDialog.LoadDialog.BindObject")

		self.pickValueEditLine.SetReturnEvent(ui.__mem_func__(self.OnAccept))
		self.pickValueEditLine.SetEscapeEvent(ui.__mem_func__(self.Close))
		self.acceptButton.SetEvent(ui.__mem_func__(self.OnAccept))
		self.cancelButton.SetEvent(ui.__mem_func__(self.Close))
		self.board.SetCloseEvent(ui.__mem_func__(self.Close))

	def Destroy(self):
		self.ClearDictionary()
		self.eventAccept = 0
		self.maxValue = 0
		self.pickValueEditLine = 0
		self.acceptButton = 0
		self.cancelButton = 0
		self.board = None

	def SetTitleName(self, text):
		self.board.SetTitleName(text)

	def SetAcceptEvent(self, event):
		self.eventAccept = event

	def SetMax(self, max):
		self.pickValueEditLine.SetMax(max)

	def Open(self, maxValue, unitValue=1):
		width = self.GetWidth()
		(mouseX, mouseY) = wndMgr.GetMousePosition()

		if mouseX + width/2 > wndMgr.GetScreenWidth():
			xPos = wndMgr.GetScreenWidth() - width
		elif mouseX - width/2 < 0:
			xPos = 0
		else:
			xPos = mouseX - width/2

		self.SetPosition(xPos, mouseY - self.GetHeight() - 20)

		self.maxValueTextLine.SetText(" / " + str(localeInfo.AddPointToNumberString(maxValue)))

		self.pickValueEditLine.SetText(str(unitValue))
		self.pickValueEditLine.SetFocus()

		ime.SetCursorPosition(1)

		self.unitValue = unitValue
		self.maxValue = maxValue
		self.Show()
		self.SetTop()

	def Close(self):
		self.pickValueEditLine.KillFocus()
		self.Hide()
		
	def __ConvertMoneyText(self, text, powers=dict(k=10**3, m=10**6, b=10**9)):
		"""
		Format string value in thousands, millions or billions.

		'1k' = 1.000
		'100kk' = 100.000.000
		'100m' = 100.000.000
		'1b' = 1.000.000.000
		'1kmb' = 1.000 (can't use multiple suffixes types)

		:param text: string
		:return: int
		:date: 10.01.2020
		:author: Vegas
		"""

		match = re.search(r'(\d+)({:s}+)?'.format('+|'.join(powers.keys())), text, re.I)
		if match:
			moneyValue, suffixName = match.groups()
			moneyValue = int(moneyValue)
			if not suffixName:
				return moneyValue

			return moneyValue * (powers[suffixName[0]] ** len(suffixName))

		return 0
		
	def OnAccept(self):
		text = self.pickValueEditLine.GetText()
		
		if text:
			moneyValue = min(self.__ConvertMoneyText(text), self.maxValue)
			
			if moneyValue:
				if self.eventAccept:
					self.eventAccept(moneyValue)

		self.Close()
		
