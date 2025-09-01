import subscription.Subscription;
import subscription.Subscriptions;
import Request.Requester;
import parser.Parser;
import feed.Feed;
import namedEntity.heuristics.Heuristic;
import namedEntity.heuristics.QuickHeuristic;
import java.io.FileWriter;
import java.io.IOException;

public class FeedReaderMain_ej3 {
	public static void main(String[] args) {
	
		Subscriptions sub = new Subscriptions("config/subscriptions_ej3.json");
	try{
		for (Subscription s: sub.getSubscriptions()){
			Requester request = new Requester(s.getUrl(),s.getUrlType());
			Feed feed = Parser.parse(request.getResponse(), request.getUrl() ,request.getType(),"True"); 
			if(s.getUrl().equals("atom")){
				FileWriter writer = new FileWriter(s.getUrl());
				writer.write(feed.toString());
			}
            Heuristic h = new QuickHeuristic();
			h.computeEntities(feed);
			h.printEntities();
		}
	}catch (Exception e){
		System.err.println(e);
	}		
	}

}
