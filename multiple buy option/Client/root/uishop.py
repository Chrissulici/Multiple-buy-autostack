#search def UnselectItemSlot(self, selectedSlotPos)::
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

#replace:
			if app.IsPressed(app.DIK_LCONTROL) and shop.GetItemMultipleBuy(selectedSlotPos) == 1:
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