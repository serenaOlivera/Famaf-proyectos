package namedEntity.heuristics;

import java.util.Set;

public class ArticleHeuristic extends Heuristic{
	protected boolean isEntity(String word){
		if (word.equals("a")){
			return true;
		}else if (word.equals("an")){
			return true;
		}else if (word.equals("the")){
			return true;
		}else if (word.equals("A")){
			return true;
		}else if (word.equals("An")){
			return true;
		}else if (word.equals("The")){
			return true;
		}else{ return false;}
	
	}

}

