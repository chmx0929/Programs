GNetMine is a graph-based regularization algorithm for classification on heterogeneous information networks. It can be viewed as a process of information propagation, where the label information is propagated from labeled objects to unlabled ones through links until a stationary state is achieved.

Given Author-Paper, Paper-Conference, Paper-Term, and Author-Conference(by A-P-C) relations.We have chosen 43 authors and 43 papers, which is listed in trainId_author.txt and trainId_paper.txt, respectively. Then the classification accuracy is evaluated by comparing with manually labeled results on the rest of the labeled objects (4014 authors, 57 papers, and 20 conferences).

Accuracy: Author:92%    Paper:85%    Conference:100%

Data Set (Heterogeneous Version):
	In the dataset we have the following files: 
	PA.txt: stores the undirected relations between paper and author. The first column is the paper ID, starting from 1, and the second column is the author ID, starting from 1.
	PC.txt: stores the undirected relations between paper and conference. The first column is the paper ID, starting from 1, and the second column is the conference ID, starting from 1.
	PT.txt: stores the undirected relations between paper and term. The first column is the paper ID, starting from 1, and the second column is the term ID, starting from 1.
	author_label.txt: contains author label information.  The first column is author id, and the second column is class id, starting from 1.
	conference_label.txt: contains conference label information.  The first column is conference id, and the second column is class id, starting from 1.
	paper_label.txt: contains paper label information.  The first column is paper id, and the second column is class id, starting from 1.
	trainId_author.txt: contains author IDs, whose label information will be used as prior knowledge.
	trainId_paper.txt: contains paper IDs, whose label information will be used as prior knowledge.
	testId_author.txt: contains author IDs, whose label information will be used in evaluation.
	testId_paper.txt: contains author IDs, whose label information will be used in evaluation.