#add
import uiPickItem

#search (def __init__(self):)
		self.itemBuyQuestionDialog = None

#add
		self.dlgPickItem = None
		
#search (def LoadDialog(self):)
		self.coinType = shop.SHOP_COIN_TYPE_GOLD
		self.Refresh()

#add
		dlgPickItem = uiPickItem.PickItemDialog()
		dlgPickItem.LoadDialog()
		dlgPickItem.Hide()
		self.dlgPickItem = dlgPickItem
		
#search (def Destroy(self):)
		self.popup = None

#add
		self.dlgPickItem.Destroy()
		self.dlgPickItem = 0
		
#search (def UnselectItemSlot(self, selectedSlotPos):)
			net.SendShopBuyPacket(self.__GetRealIndex(selectedSlotPos))

#replace
			if app.IsPressed(app.DIK_LCONTROL):
				itemIndex = shop.GetItemID(selectedSlotPos)
				item.SelectItem(itemIndex)
				itemName = item.GetItemName()
				self.dlgPickItem.SetTitleName(itemName)
				self.dlgPickItem.SetAcceptEvent(ui.__mem_func__(self.OnPickItem))
				self.dlgPickItem.Open(200)
				self.dlgPickItem.SetMax(200)
				self.dlgPickItem.itemGlobalSlotIndex = selectedSlotPos
			else:
				net.SendShopBuyPacket(self.__GetRealIndex(selectedSlotPos))
		
#add
	def OnPickItem(self, count):
		itemSlotIndex = self.dlgPickItem.itemGlobalSlotIndex
		n = 0

		while n < count:
			net.SendShopBuyPacket(self.__GetRealIndex(itemSlotIndex))
			n = n + 1

