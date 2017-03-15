The query input is a researcher's id, and the output is the top-5 most similar researchers' ids. In this specific case, we output the top-5 ranked results (i.e., similar researchers) for author id 7696, taking APVPA (autho -paper-venue-paper-author) and APTPA (author-paper-term-paper- author) as meta-paths respectively.

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