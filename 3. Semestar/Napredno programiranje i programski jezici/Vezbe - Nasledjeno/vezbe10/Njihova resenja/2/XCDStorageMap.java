package z2;

import java.util.HashMap; 


public class XCDStorageMap {
	
	private HashMap<Integer, CDDisk> arhiva;
	
	public XCDStorageMap() {
		arhiva = new HashMap<Integer, CDDisk>();
	}
	
	public boolean add(CDDisk d) {
		if(arhiva.containsKey(d.getId()))
			return false;

		arhiva.put(d.getId(), d);
		return true;
	}
	
	public CDDisk remove(int id) {
		return arhiva.remove(id);
	}
	
	public CDDisk find(int id) {
		return arhiva.get(id);
	}
	
	public void clear(){
		arhiva.clear();
	}
	
	@Override
	public String toString() {
		if(arhiva.isEmpty()) return "U arhivi nema diskova!";
		
		String retVal = "Sadrzaj CD arhive je:\n";
		for(CDDisk d: arhiva.values())
			retVal += d + "\n";
		
		return retVal;
	}

}
