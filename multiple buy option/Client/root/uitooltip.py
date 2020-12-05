#search def SetShopItem(self, slotIndex)::
		self.AppendSpace(5)
		self.AppendTextLine(localeInfo.EMOJI_MULTIPLE_BUY_SHOP, self.CAN_LEVEL_UP_COLOR)

#replace:
		if shop.GetItemMultipleBuy(slotIndex) == 1:
			self.AppendSpace(5)
			self.AppendTextLine(localeInfo.EMOJI_MULTIPLE_BUY_SHOP, self.CAN_LEVEL_UP_COLOR)