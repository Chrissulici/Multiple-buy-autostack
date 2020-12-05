//search:
PyObject * shopGetTabCoinType(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bTabIdx;
	if (!PyTuple_GetInteger(poArgs, 0, &bTabIdx))
		return Py_BuildException();

	return Py_BuildValue("i", CPythonShop::instance().GetTabCoinType(bTabIdx));
}

//add:
PyObject * shopGetItemMultipleBuy(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TShopItemData * c_pItemData;
	if (CPythonShop::Instance().GetItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->multiple_buy);

	return Py_BuildValue("i", 0);
}
		
//search:
		{ "GetTabCoinType",				shopGetTabCoinType,				METH_VARARGS },

//add:
		{ "GetItemMultipleBuy",			shopGetItemMultipleBuy,			METH_VARARGS },
		
