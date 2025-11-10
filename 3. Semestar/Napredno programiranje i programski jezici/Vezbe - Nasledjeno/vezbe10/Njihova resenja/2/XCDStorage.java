package z2;

import java.util.ArrayList; 

public class XCDStorage {
	
	private ArrayList<CDDisk> arhiva;
	
	public XCDStorage() {
		arhiva = new ArrayList<CDDisk>();
	}
	
	public boolean add(CDDisk d) {
		for(int i = 0; i < arhiva.size(); i++)
			if((arhiva.get(i)).getId() == d.getId())
				return false;
		
		return arhiva.add(d);
	}
	
	public CDDisk remove(int id) {
		for(int i = 0; i < arhiva.size(); i++)
			if((arhiva.get(i)).getId() == id)
				return arhiva.remove(i);
		
		return null;
	}
	
	public CDDisk find(int id) {
		for(int i = 0; i < arhiva.size(); i++)
			if((arhiva.get(i)).getId() == id)
				return arhiva.get(i);
		
		return null;
	}
	
	public void clear(){
		arhiva.clear();
	}
	
	@Override
	public String toString() {
		if(arhiva.isEmpty()) return "U arhivi nema diskova!";
		
		String retVal = "Sadrzaj CD arhive je:\n";
		for(int i = 0; i < arhiva.size(); i++)
			retVal += arhiva.get(i) + "\n";
		
		// alternativni oblik prethodne for petlje
		//		for(CDDisk d: arhiva)
		//			retVal += d + "\n";
		
		return retVal;
	}
	

}
