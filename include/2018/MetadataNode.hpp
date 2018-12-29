#ifndef INCLUDED_ADVENT_OF_CODE_2018_METADATA_NODE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_METADATA_NODE_HPP_

#include <vector>

namespace TwentyEighteen {
	
	struct MetadataNode {
		MetadataNode(int _numberChildren, int _numberMetadata) :
			NumberChildren(_numberChildren), NumberMetadata(_numberMetadata) {

		}

		std::vector<MetadataNode> children;
		std::vector<int> metadata;

		int const NumberChildren;
		int const NumberMetadata;
	};
}

#endif // INCLUDED_ADVENT_OF_CODE_2018_METADATA_NODE_HPP_