import subscription.Subscription;
import subscription.Subscriptions;
import Request.Requester;
import parser.Parser;
import feed.Feed;
import namedEntity.heuristics.Heuristic;
import namedEntity.heuristics.ArticleHeuristic;


public class FeedReaderMain_ej2 {
	public static void main(String[] args) {
	
		Subscriptions sub = new Subscriptions("config/subscriptions_ej2.json");
		for (Subscription s: sub.getSubscriptions()){
			Requester request = new Requester(s.getUrl(),s.getUrlType());
			Feed feed = Parser.parse(request.getResponse(), request.getUrl() ,request.getType(),"True"); 
			
            Heuristic h = new ArticleHeuristic();
			h.computeEntities(feed);
			h.printEntities();			
		
        }
	}
}
