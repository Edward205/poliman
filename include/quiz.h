#pragma once

#include <vector>
#include <utility>
#include <string>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "include/button.h"
#include "include/font_renderer.h"

class Quiz {
public:
    bool active;
    int questionIndex;
    int state = 0; // 0 = unanswered; 1 = correct answer; 2 = wrong answer
    void triggerQuiz();
    void handleInput(SDL_Event e);
    void render(SDL_Renderer* renderer);
    void init(SDL_Renderer* renderer);
    ~Quiz();
private:
// TODO THIS IS REALLY BAD
    FontRenderer* question;
    Button* answer1;
    Button* answer2;
    Button* answer3;
    Button* answer4;


    std::vector<std::pair<std::string, bool>> quizes = {
    {"What is the ability of machines to perform tasks that would normally require human intelligence?", false},
    {"Artificial intelligence", true},
    {"Data science", false},
    {"Data learning", false},
    {"Machine intelligence", false},

    {"What is the name of the field of AI that focuses on developing algorithms to extract information from images and videos?", false},
    {"Computer vision", true},
    {"Natural language processing", false},
    {"Video translation", false},
    {"None of the answers", false},

    {"What is the most important thing to keep in mind when developing and deploying AI systems?", false},
    {"All the answers", true},
    {"AI systems should be aligned with human values", false},
    {"AI systems need to be transparent and accountable", false},
    {"AI systems should be made to be fair and unbiased", false},
    
    {"What is the most important thing that we need to do to ensure that AI is accessible to everyone?", false},
    {"All the answers", true},
    {"Invest in education and training to ensure that everyone has the skills and knowledge to use AI", false},
    {"Promote the responsible development and use of AI", false},
    {"Develop affordable and accessible AI tools and resources", false},

    {"What is the future of AI?", false},
    {"All the answers", true},
    {"AI will be used to replace humans for manual tasks", false},
    {"AI will be used to solve challenges that humans can't", false},
    {"AI will become a big part of our lives", false},

    {"What is artificial intelligence (AI)?", false},
    {"The ability of machines to mimic human behavior.", false},
    {"The ability of machines to think and learn like humans.", false},
    {"The ability of machines to perform tasks that would normally require human input.", true},
    {"All the rest", false},

    {"What is the name of the field of AI that focuses on developing algorithms to understand and generate natural language?", false},
    {"Natural language processing (NLP)", true},
    {"Speech recognition", false},
    {"Computer vision", false},
    {"None of the answers", false},

    {"What type of AI algorithm can be used for ads?", false},
    {"Recommendation engine", true},
    {"Guess engine", false},
    {"Ads learning", false},
    {"Tracking engine", false},

    {"Which of the following is NOT a potential benefit of AI?", false},
    {"Making certain jobs not needed anymore", true},
    {"Increasing productivity", false},
    {"Creating new products and services", false},
    {"Improving decision making", false},

    {"Which of the following is NOT a way to measure the success of an AI system?", false},
    {"Social impact", true},
    {"Recall", false},
    {"Accuracy", false},
    {"Precision", false},

    {"How can we mitigate bias in AI?", false},
    {"use a diverse dataset", true},
    {"use more data", false},
    {"use biased data", false},
    {"use less data", false},

    {"What possible consequences can bias in AI lead to?", false},
    {"discrimination", true},
    {"efficiency", false},
    {"accuracy", false},
    {"transparency", false},

    {"What is the main cause of bias in AI programming?", false},
    {"data bias", false},
    {"human bias", false},
    {"algorithmic bias", true},
    {"judgment bias", false},

    {"Which of the following is NOT an example of algorithmic bias in AI?", false},
    {"A search engine that is more likely to return results for popular websites than for less popular websites.", true},
    {"A spam filter that is more likely to flag emails from women than from men.", false},
    {"A resume screening algorithm that is more likely to recommend male candidates for high-paying jobs than female candidates.", false},
    {"A facial recognition algorithm that is more accurate at identifying white people than black people.", false},

    {"Which can be an option to avoid bias in AI-powered decisions?", false},
    {"have human oversight", true},
    {"don't use AI to take those decisions", false},
    {"create a separate AI to validate the first one", false},
    {"only use AI for small decisions", false},

    {"Which one is a way to mitigate bias in AI?", false},
    {"Create audit systems for bias", true},
    {"Don't use the products", false},
    {"Highlight the bias and ignore it", false},
    {"Don't question the output of the application", false},

    {"What is a possible consequence of bias in AI?", false},
    {"Unfair outcomes", true},
    {"Transparent outcomes", false},
    {"Good enough outcomes", false},
    {"Accurate outcomes", false},

    {"What is a correct definition for bias in AI?", false},
    {"Bias in AI programming can lead to apps that favor a certain group of people or certain result", true},
    {"Bias in AI programming can lead to apps that make mistakes", false},
    {"Bias in AI programming can lead to apps that are inefficient", false},
    {"Bias in AI programming can lead to apps that are created only for a certain situation", false},

    {"What is a cause of bias in AI?", false},
    {"All the rest", true},
    {"Data used to train the AI is not representative for the whole population", false},
    {"The AI inherits the bias of the programmers", false},
    {"The AI is too rudimentary to differentiate human nuances", false},

    {"Who is responsible for fighting and mitigating bias in AI programming?", false},
    {"All the rest", true},
    {"The programmers", false},
    {"The private companies", false},
    {"The public sector", false},

    {"Which of the following is a benefit of using AI to protect privacy?", false},
    {"all the rest", true},
    {"AI tools can be used to develop new encryption algorithms", false},
    {"AI tools can be used to identify and remove personally identifiable information from data", false},
    {"AI tools can be used to discover data breaches in the systems", false},

    {"Which of the following is NOT a type of privacy-preserving AI?", false},
    {"Centralized learning", true},
    {"Differential privacy", false},
    {"Federated learning", false},
    {"Secure multi-party computation", false},

    {"Which of the following is the most important thing to keep in mind when thinking about privacy in AI?", false},
    {"Before releasing an AI product we need to prioritize the privacy elements of the system", true},
    {"We can leave privacy element outside the system as those aren't mandatory", false},
    {"Privacy is just o module that need to be integrated", false},
    {"Privacy concerns need to be addressed only when surfaced by users", false},

    {"Which of the following is a challenge to implementing privacy-preserving AI?", false},
    {"All the rest", true},
    {"The need to educate developers and users about privacy-preserving AI.", false},
    {"The need to develop new algorithms and techniques.", false},
    {"The need to address the potential for trade-offs between privacy and other important goals, such as accuracy and efficiency.", false},

    {"What is the difference between personally identifiable information (PII) and non-personally identifiable information (non-PII)?", false},
    {"PII is information that can be used to identify a specific individual, while non-PII information that cannot be used to identify a specific individual on its own", true},
    {"PII is information that is used by businesses, while non-PII is information that is used by governments", false},
    {"PII is information that is publicly available, while non-PII is information that is not publicly available", false},
    {"PII is information that is collected online, while non-PII is information that is collected offline", false},

    {"Which of the following is NOT a privacy-preserving AI practice?", false},
    {"Data sharing", true},
    {"Data anonymization", false},
    {"Data minimization", false},
    {"Data differential privacy", false},

    {"Which of the following is an example of privacy-preserving AI?", false},
    {"An assistant that respond to natural language", false},
    {"A facial recognition tool to identify people on the street", false},
    {"A recommendation tool that can offer suggestion based on past purchases", false},
    {"All the other options", false},

    {"Which of the following is NOT a way to address privacy concerns related to AI?", false},
    {"Using AI tools to gather more data from users", true},
    {"Developing transparent AI products", false},
    {"Giving users access and control over their data", false},
    {"Creating privacy laws, regulations and principles", false},

    {"What is a privacy preserving AI principle?", false},
    {"Using AI to process data so that it protects individual privacy", true},
    {"Using AI to discriminate against individuals based on their data", false},
    {"Using AI to collect as much data as possible about individuals", false},
    {"Using AI to make decisions about individuals without their knowledge or consent", false},

    {"Which of the following is a risk when it comes to privacy when using AI-powered social media products?", false},
    {"All the rest", true},
    {"AI tools can be used to track our online presence and collect personal data without our knowledge or consent", false},
    {"AI tools can be used to target users with personalized ads and content that is designed without our knowledge or consent", false},
    {"AI tools can be used to create deep fakes that can be used to spread misinformation or damage the reputation of individuals or oganizations", false},

    {"Which of the following answers is NOT a benefit of transparency in AI ethics?", false},
    {"It makes AI systems more accurate", true},
    {"It helps to identify and mitigate ethical risks.", false},
    {"It helps to build trust in AI.", false},
    {"It helps to ensure that AI is used responsibly.", false},

    {"Which of the following answers is NOT a challenge to achieving transparency in AI ethics?", false},
    {"AI developers are reluctant to share information about their systems.", false},
    {"There is no general solution to solve transparency in AI", false},
    {"There isn't a standard or a guideline for AI transparency", false},
    {"AI system are complex and difficult to explain", true},

    {"Which of the following is an example of a transparency-enhancing measure in AI ethics?", false},
    {"All other answers.", true},
    {"Publish the technical documentation for AI models and algorithms.", false},
    {"Provide users with access to information about the data used to train AI models.", false},
    {"Develop tools for explainable AI.", false},

    {"Which of the following is NOT expected from an ethical reviewer?", false},
    {"Approving or rejecting the AI system for release.", true},
    {"Reviewing the AI system to detect transparency issues.", false},
    {"Provide guidance on how to develop the AI tools.", false},
    {"Create documentation on how the AI system can become transparent.", false},

    {"Which of the following is the most important thing that can be done to promote transparency in AI ethics?", false},
    {"All other answers.", true},
    {"Hold AI programmers and their organizations accountable.", false},
    {"Educate users on how AI systems work.", false},
    {"Create playbooks on how AI systems can be more transparent.", false},

    {"Which of the following is NOT a way to measure transparency in AI ethics?", false},
    {"The public's understanding of AI and how it works.", false},
    {"The number of AI systems that are subject to ethical review.", false},
    {"The number of published papers related to AI ethics.", true},
    {"The understanding of programmers related to AI ethics.", false},

    {"Which of the following is NOT a potential cost of transparency in AI ethics?", false},
    {"Increased public trust in the AI products.", true},
    {"Decreased accuracy of the AI products.", false},
    {"Increased cost of developing and maintaining the AI products.", false},
    {"Increased risk of data privacy issues.", false},

    {"Which of the following is NOT a way to make AI systems more explainable?", false},
    {"All other answers.", false},
    {"Create visualization tools.", false},
    {"Use smaller data samples.", true},
    {"Use rudimentary algorithms.", true},

    {"Which of the following is the best way to ensure transparency in AI ethics?", false},
    {"A hybrid approach, with governments, NGOs and industry working together to develop and implement transparency standards.", true},
    {"A top-down approach, with governments and regulators mandating transparency requirements.", false},
    {"Don't implement any regulation or practices.", false},
    {"A bottom-up approach, with AI companies and developers voluntarily adopting transparency practices.", false},

    {"Which of the following is NOT a challenge to achieving transparency in AI ethics?", false},
    {"All the rest", false},
    {"Lack of expertise.", true},
    {"Lack of resources.", true},
    {"Lack of time.", true}

    };
};