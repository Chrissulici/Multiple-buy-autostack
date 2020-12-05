//search:
class CShop
{
	public:
		typedef struct shop_item
		{
			DWORD		vnum;	
			long long	price;	
			WORD		count;

//add:
			BYTE		multiple_buy;
			
//search:
			LPITEM		pkItem;
			int			itemid;	
			shop_item()
			{
				vnum = 0;
				price = 0;
				count = 0;

//add:
				multiple_buy = 0;