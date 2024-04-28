#if !defined(MESSAGE_CONTROLLER_HPP)
#define MESSAGE_CONTROLLER_HPP

#include "CommandData.hpp"
#include "Client.hpp"
#include <cstring>
#include <sstream>
#include <map>
#include <vector>
/**
 * @class MessageController
 *
 * Այս դասը ծառայում է որպես IRC սերվերի հավելվածում հաղորդագրությունների մշակման կենտրոնական հանգույց: Այն ներառում է գործառույթները հետևյալի համար.
 *
 * - Վերլուծություն. բաժանում է հաճախորդներից ստացված հաղորդագրությունները առանձին IRC հրամանների, որոնք ներկայացված են «CommandData» օբյեկտներով:
 * - Վավերացում. Ապահովում է, որ ալիքի և մականվան ձևաչափերը համապատասխանում են IRC արձանագրության բնութագրերին:
 * - Հաղորդագրությունների վերակառուցում. մշակում է պոտենցիալ մասնատված հաղորդագրությունները, որոնք ստացվել են կտորներով՝ դրանք հավաքելով ամբողջական հաղորդագրությունների:
 * - Տողերի մանիպուլյացիայի կոմունալ ծառայություններ. տրամադրում է օգնական գործառույթներ հաղորդագրության մշակման մեջ օգտագործվող սովորական տողային գործողությունների համար:
 *
 * «MessageController»-ը պահպանում է ներքին քարտեզ («chunksMap»)՝ հատուկ հաճախորդի վարդակների հետ կապված հաղորդագրությունների հատվածներին հետևելու համար: Սա թույլ է տալիս դասին վերականգնել ամբողջական հաղորդագրությունները, նույնիսկ եթե դրանք հասնում են մի քանի մասերի:
 */
class MessageController
{
	/**
     * «MessageController»-ի կանխադրված կոնստրուկտոր:
     */
    MessageController();

   /**
     * Destructor «MessageController»-ի համար: Պատասխանատու է պատշաճ մաքրման համար (անհրաժեշտության դեպքում):
     */
    ~MessageController();

public:
   /**
     * Վերլուծում է պոտենցիալ բազմաթիվ IRC հրամաններ պարունակող տողը, որոնք առանձնացված են տողերի ընդմիջումներով (`\n`):
     * Յուրաքանչյուր հրաման արդյունահանվում և վերածվում է համապատասխան «CommandData» օբյեկտի՝ ձևավորելով վեկտոր, որը ներկայացնում է վերլուծված հրամանները:
     *
     * @param մուտքագրում վերլուծվող հաղորդագրությունը պարունակող տողը:
     * @return «CommandData» օբյեկտների վեկտոր, որը ներկայացնում է վերլուծված հրամանները:
     */
    std::vector<CommandData> Parse(std::string &input) const;

 
	/**
     * Վերլուծում է մեկ IRC հրամանի տողը (առանց տողերի ընդմիջումների) «CommandData» օբյեկտի մեջ: Սա սովորաբար օգտագործվում է ավելի մեծ հաղորդագրությունից արդյունահանվող առանձին հրամանների մշակման համար:
     *
     * @param singleCommand Տող, որը պարունակում է վերլուծվող մեկ հրաման:
     * @return «CommandData» օբյեկտ, որը ներկայացնում է վերլուծված հրամանը:
     */
    CommandData ParseSingleCommand(const std::string &singleCommand) const;

  /**
     * Տպում է «CommandData» օբյեկտների վեկտորի բովանդակությունը ելքային հոսքի վրա (սովորաբար կոնսոլը կամ գրանցամատյան ֆայլը) վրիպազերծման կամ գրանցման նպատակով:
     *
     * @param data Տպվող «CommandData» օբյեկտների վեկտորը:
     */
    void PrintData(std::vector<CommandData> &data) const;

   
/**
     * Վավերացնում է, թե արդյոք տվյալ տողը համապատասխանում է վավեր IRC ալիքի անվանման ձևաչափի պահանջներին:
     *
     * @param channelName Վավերացվող տողը:
     * @return Ճիշտ է, եթե տողը վավեր ալիքի անուն է, հակառակ դեպքում՝ կեղծ:
     */
    bool IsValidChannelName(const std::string &channelName) const;

   /**
     * Վավերացնում է, թե արդյոք տվյալ տողը համապատասխանում է վավեր IRC մականվան ձևաչափի պահանջներին:
     *
     * @param Մականուն Վավերացվող տողը:
     * @return Ճիշտ է, եթե տողը վավեր մականուն է, հակառակ դեպքում՝ կեղծ:
     */
    bool IsValidNickname(const std::string &nickname) const;

    
/**
     * Ստուգում է, արդյոք տրված տողը սկսվում է նշված նիշերի հավաքածուից որևէ նշանով:
     * Սա կարող է օգտակար լինել հատուկ հրամանների նախածանցները բացահայտելու համար (օրինակ՝ «/»):
     *
     * @param str Ստուգվող տողը։
     * @param set Նիշերի հավաքածու, որոնց դեմ պետք է ստուգել:
     * @return Ճիշտ է, եթե տողը սկսվում է բազմության գրանշանով, հակառակ դեպքում՝ կեղծ:
     */
    bool StringStartsWithFromSet(const std::string &str, const std::string &set) const;

  /**
     * Որոշում է, թե արդյոք ստացվել է հաղորդագրության հատված որոշակի հաճախորդի վարդակից:
     * Սա օգտագործվում է մասամբ ստացված հաղորդագրություններին հետևելու համար, որոնք կարող են մասնատված լինել ցանցի սահմանափակումների պատճառով:
     *
     * @param clientSocket Հաճախորդի վարդակից նույնացուցիչը:
     * @return Ճիշտ է, եթե հաճախորդի համար կա հաղորդագրության հատված, հակառակ դեպքում՝ կեղծ:
     */
    bool ContainsChunk(int clientSocket) const;

   /**
     * Հաճախորդից ստացված հաղորդագրության կտոր է ավելացնում ներքին քարտեզին (`chunksMap`), որը պահում է հաղորդագրությունների հատվածները հաճախորդների համար մինչև ամբողջական հաղորդագրությունը կառուցվի:
     *
     * @param clientSocket Հաճախորդի վարդակից նույնացուցիչը:
     * @param messageChunk Ստացված հաղորդագրության հատվածը պարունակող տողը:
     */
		void	AddChunk(int clientSocket, const std::string &messageChunk);
		void	ClearChunk(int clientSocket);
		std::string	ConstructFullMessage(int clientSocket);
		std::string trim(std::string const &str)const;
		std::string	GetModesString(const std::string &argument, char sign) const;
		int	SignCount(const std::string &str, char sign) const;



		static	MessageController	*getController();

	private:
		std::map<int, std::vector<std::string> > chunksMap;
		static MessageController *instance;
};




#endif // MESSAGE_CONTROLLER_HPP
