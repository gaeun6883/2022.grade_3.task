import java.io.*;
import java.util.*;
import java.util.Map.Entry;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class MyCompString implements Comparator<String> {
	public int compare(String a, String b) {
		return a.compareTo(b);
	}
}

class MyCompOne implements Comparator<HashMap.Entry<String, Integer>> {
	public int compare(HashMap.Entry<String, Integer> a, HashMap.Entry<String, Integer> b) {
		if(b.getValue()==a.getValue())
			return a.getKey().compareTo(b.getKey());
		return b.getValue().compareTo(a.getValue());
	}
}

class MyCompSub implements Comparator<HashMap.Entry<String, String>> {
	public int compare(HashMap.Entry<String, String> a, HashMap.Entry<String, String> b) {
		if(b.getKey()==a.getKey())
			return a.getValue().compareTo(b.getValue());
		return a.getKey().compareTo(b.getKey());
	}
}

class MyCompPair implements Comparator<HashMap.Entry<HashMap.Entry<String, String>, Integer>> {
	MyCompSub sub=new MyCompSub();
	public int compare(HashMap.Entry<HashMap.Entry<String, String>, Integer> a, HashMap.Entry<HashMap.Entry<String, String>, Integer> b) {
		if(a.getValue()==b.getValue()) 
			return sub.compare(a.getKey(), b.getKey());
		return b.getValue().compareTo(a.getValue());
	}
}


public class HW3 {
	static HashMap<String, Integer> stopWord = new HashMap<>();
	static HashMap<String, Integer> listOne = new HashMap<>();
	static HashMap<HashMap.Entry<String, String>, Integer> listPair = new HashMap<>();

	public static void main(String[] args) {
		try {
			FileReader filereader = new FileReader("stop.txt");
			BufferedReader bufReader = new BufferedReader(filereader);
			String word = "";
			while ((word = bufReader.readLine()) != null) {
				word = word.trim();
				String[] str = word.split(" ");
				for (String s : str)
					stopWord.put(s, 1);
			}
		} catch (IOException e) {
			System.out.println("파일입력 오류");
			return;
		}

		System.out.print("파일 이름, 단어 쌍의 수? ");
		Scanner in = new Scanner(System.in);
		String f = in.next();
		int k = in.nextInt();
		int idx = 0;
		try {
			File file = new File(f);
			FileReader filereader = new FileReader(file);
			BufferedReader bufReader = new BufferedReader(filereader);
			String line = "", tmpS = "", tmpW = "";
			while ((line = bufReader.readLine()) != null) {
				if (line.equals(""))
					continue;
				line = line.toLowerCase();
				String sentence[] = line.split("\\.|\\!|\\?");
				if (sentence.length == 0) continue;
				if (!tmpS.equals("")) {
					sentence[0] = tmpS + sentence[0];
					tmpS = "";
				}
				if (line.charAt(line.length() - 1) != '.' && line.charAt(line.length() - 1) != '!'&& line.charAt(line.length() - 1) != '?') {
					tmpS = sentence[sentence.length - 1] + " ";
					sentence[sentence.length - 1] = "";
				}

				for (int i = 0; i < sentence.length; i++) {
					if (sentence[i].equals("")) continue; 
					String sen = sentence[i].trim();
					String[] word = sen.split("[^a-z|-]");
					for (int a = 0; a < word.length; a++) {
						if (stopWord.containsKey(word[a]) || word[a].equals("")) continue;
						if (listOne.containsKey(word[a])) {
							int cnt = listOne.get(word[a]) + 1;
							listOne.put(word[a], cnt);
						}
						else listOne.put(word[a], 1);
					}
					
					List<String> w = new LinkedList<>();
					for (int a = 0; a < word.length; a++) {
						if (stopWord.containsKey(word[a]) || word[a].equals("")) continue;
						boolean state=true;
						for (int b = 0; b < a; b++) 
							if (word[a].equals(word[b]))
								state=false;
						if(state)
							w.add(word[a]);
					}
					Collections.sort(w, new MyCompString());
					for (int a = 0; a < w.size(); a++)
						for (int b = a + 1; b < w.size(); b++) {
							Map<String, String> str = new HashMap<>();
							str.put(w.get(a), w.get(b));
							for (Map.Entry<String, String> m : str.entrySet())
								if (listPair.containsKey(m)) 
									listPair.put(m, listPair.get(m) + 1);
								else listPair.put(m, 1);
						}
				}
			}
		} catch (IOException e) {
			System.out.println("파일입력 오류");
			return;
		}
		
		List<HashMap.Entry<String, Integer>> sortedOne = new ArrayList<>(listOne.entrySet());
		Collections.sort(sortedOne, new MyCompOne());
		System.out.print("Top-k 문자열: ");
		for (int i = 0; i < k; i++)
			System.out.print(sortedOne.get(i).getKey() + "(" + sortedOne.get(i).getValue() + ") ");
		System.out.print('\n');

		List<HashMap.Entry<HashMap.Entry<String, String>, Integer>> sortedPair = new LinkedList<>(listPair.entrySet());
		Collections.sort(sortedPair, new MyCompPair());
		System.out.print("Top-k 단어쌍: ");
		for (int i = 0; i < k; i++)
			System.out.print("[" + sortedPair.get(i).getKey().getKey() + "," + sortedPair.get(i).getKey().getValue()+ "](" + sortedPair.get(i).getValue() + ") ");
	}
}