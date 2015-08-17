#include "Exploradoras.h"

 std::pair<int, std::string> Exploradoras::backtracking(std::vector<std::pair<char, std::string>> explorers_relations) {

	 unsigned int letters = 26;

     std::vector<std::vector<bool>> friendship_table(letters, std::vector<bool>(letters, false));
//     std::vector<std::vector<bool>> visited(letters, std::vector<bool>(letters, false));

	 std::string explorers(explorers_relations.size(), 0);

	 int e = 0;

	 for (auto i = explorers_relations.begin(); i != explorers_relations.end(); i++, e++) {
        char explorer = std::get<0>(*i);
        std::string friends = std::get<1>(*i);

        explorers[e] = explorer;

        for (auto j = friends.begin(); j != friends.end(); ++j) {
            friendship_table[explorer - 'a'][*j - 'a'] = true;
            friendship_table[*j - 'a'][explorer - 'a'] = true;
            }
	}

	std::sort(explorers.begin(), explorers.end());

	auto min_distance = INTMAX_MAX;
	std::string best_seats;

	do {

		for (e = 0; e < explorers.size(); e++) {
			unsigned int current_distance = 0;
//			int left = (e-1) < 0 ? explorers.size()-1 : (e-1);
//			int right = (e+1) == explorers.size() ? 0 : (e+1);
//			unsigned int stride = 1;

            for (int start = e+1; start < explorers.size(); ++start) {
                bool is_friend = friendship_table[explorers[e]-'a'][explorers[start]-'a'];
                current_distance += std::min(start, ((int)explorers.size()) - start) * is_friend;
            }

//			for (; left != right; stride++) {
//                bool is_friend_left = friendship_table[explorers[e]-'a'][explorers[left]-'a'];
//                bool is_friend_right = friendship_table[explorers[e]-'a'][explorers[right]-'a'];
//
//                bool checked_left = visited[explorers[e]-'a'][explorers[left]-'a'];
//                bool checked_right = visited[explorers[e]-'a'][explorers[right]-'a'];
//
//				current_distance += (!checked_left) * is_friend_left * stride;
//				current_distance +=  (!checked_right) * is_friend_right * stride;
//
//                visited[explorers[e]-'a'][explorers[left]-'a'] = visited[explorers[left]-'a'][explorers[e]-'a'] = true;
//                visited[explorers[e]-'a'][explorers[right]-'a'] = visited[explorers[right]-'a'][explorers[e]-'a'] = true;
//
//				left = (left-1) < 0 ? explorers.size()-1 : (left-1);
//				right = (right + 1) == explorers.size() ? 0 : (right+1);
//			}
//
//			current_distance += friendship_table[explorers[e]-'a'][explorers[left]-'a'] * (stride+1);

			if (current_distance < min_distance) {
				min_distance = current_distance;
				best_seats = explorers;
			}

		}

//        for (int i = 0; i < letters; ++i) {
//            for (int j = 0; j < letters; ++j) {
//                visited[i][j] = false;
//            }
//        }

	} while (next_permutation(explorers));

	return std::make_pair(min_distance, best_seats);
}


#define SWAP(a, b)  {auto temp = a; a = b; b = temp;}

bool Exploradoras::next_permutation(std::string perm){

	auto n = (int)perm.size();
	auto i = 0;
	bool next_p = false;

	for(; i < n - 1; i++){
		if (perm[i] < perm[i+1]){
            next_p = true;
            break;
        }
	}

    if (!next_p){
        return false;
    }

    i = n - 1;

    for(; perm[i-1] >= perm[i]; i--);
	auto j = n;

    for(; perm[j-1] >= perm[i-1]; j--);

    SWAP(perm[i-1], perm[j-1]);

    i++;
	j = n;

    for(; i < j; i++, j--){
        SWAP(perm[i-1], perm[j-1]);
    }
	return next_p;
}



/*
COMPLEJIDAD TOTAL:
e! . (e . e . a  + e) = e!. e2.a + e
*/

