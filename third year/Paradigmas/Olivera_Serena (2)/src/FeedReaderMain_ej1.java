import subscription.Subscription;
import subscription.Subscriptions;
import Request.Requester;
import parser.Parser;
import feed.Feed;


public class FeedReaderMain_ej1 {
	public static void main(String[] args) {
	
		Subscriptions sub = new Subscriptions("config/subscriptions_ej1.json");
		for (Subscription s: sub.getSubscriptions()){
			Requester request = new Requester(s.getUrl(),s.getUrlType());
		if (s.getContent().equals("True")){	
			Feed feed = Parser.parse(request.getResponse(), request.getUrl(), request.getType(), "True");
			feed.prettyPrint();
		} else if (s.getContent().equals("False")){
			Feed feed = Parser.parse(request.getResponse(), request.getUrl(), request.getType(), "False");
			feed.prettyPrint();			
		}
			

			
		}
	}
}
