import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

class MyCompDouble implements Comparator<Map.Entry<String, Double>>{
	public int compare(Map.Entry<String, Double> a, Map.Entry<String, Double> b) {
		return(a.getValue()==b.getValue())? a.getKey().compareTo(b.getKey()): b.getValue().compareTo(a.getValue());  
	}
}

class MyCompInt implements Comparator<Map.Entry<Integer, Integer>>{
	public int compare(Map.Entry<Integer, Integer> a, Map.Entry<Integer, Integer> b) {
		return(a.getValue()==b.getValue())? a.getKey().compareTo(b.getKey()): b.getValue().compareTo(a.getValue());  
	}
}

public class HW2 {
	public static void main(String[] args) {
		System.out.printf("피일 이름, 사용자 이름, 사용자 수, 항목 수? ", "MS949");
		Scanner in=new Scanner(System.in);
		String f=in.next();
		String x=in.next();
		int n=in.nextInt();
		int m=in.nextInt();
		HashMap<String,Set<String>> map = new HashMap<>();
		try {
			File file=new File(f);
		    FileReader filereader=new FileReader(file);
		    BufferedReader bufReader=new BufferedReader(filereader);
		    String word="";
		    while((word=bufReader.readLine())!=null) {
		    	word=word.trim();
		    	String[] str=word.split(" ");
		    	Set<String> list =new HashSet<>();
		    	for(int i=1; i<str.length; i++)
		    		list.add(str[i]);
		    	map.put(str[0], list);
		    }
		}catch(IOException e) {
			System.out.println("파일입력 오류");
			return;
		}
		
		HashMap<String,Double> similar = new HashMap<>();
		Set<String> s1=new HashSet<>(map.get(x));
		for(String key:map.keySet()) {
			if(key.equals(x)) continue;
			Set<String> union=new HashSet<>(map.get(key));
			Set<String> intersection=new HashSet<>(map.get(key));
			union.addAll(s1);
			intersection.retainAll(s1);
			if(intersection.size()==0) continue;
			double similarity=(intersection.size()*1.0)/(union.size()*1.0);
			similar.put(key,similarity);
		}
		List<Map.Entry<String, Double>> sortSimilar= new LinkedList<>(similar.entrySet());
		Collections.sort(sortSimilar, new MyCompDouble());
		
		HashMap<Integer,Integer> recommand = new HashMap<>();
		for(int i=0; i<n; i++) {
			String ob=sortSimilar.get(i).getKey();
			Set<String> differential=new HashSet<>(map.get(ob));
			differential.removeAll(s1);
			Iterator<String> iter=differential.iterator();
			while(iter.hasNext()) {
				String num=iter.next();
				int Num=Integer.parseInt(num);
				if(recommand.containsKey(Num)) {
					int cnt=recommand.get(Num)+1;
					recommand.put(Num, cnt);
				}
				else recommand.put(Num, 1);
			}
		}
		List<Map.Entry<Integer, Integer>> sortRecommand= new ArrayList<>(recommand.entrySet());
		Collections.sort(sortRecommand, new MyCompInt());
		
		for(int i=0; i<m; i++) 
			System.out.print(sortRecommand.get(i).getKey().+"("+sortRecommand.get(i).getValue()+") ");
	}
}