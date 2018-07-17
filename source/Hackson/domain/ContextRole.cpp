#include "Hackson/domain/Node.h"
#include "Hackson/domain/Edge.h"
#include "Hackson/domain/Graph.h"
#include "Hackson/domain/BestGraph.h"
#include "Hackson/domain/ContextRole.h"
#include "Hackson/domain/NodeMapRole.h"
#include "Hackson/domain/ShortestEdgeRole.h"

void ContextRole :: formShortestEdgeBetweenTwoGraph(const Graph& graph, const BestGraph& bestGraph)
{
	for(int index = 0; index < graph.getAllNodeNum(); index++)
	{
		int lowestWeight = INVALID_VALUE;
		Edge* bestEdge   = NULL;

		if(ROLE(NodeMapRole).isNodeInBestGraph(index))
		{
			if(ROLE(ShortestEdgeRole).hasEdgeBetweenTwoGraphByIndex(index))
			{
			    if(!ROLE(NodeMapRole).isNodeInBestGraph(ROLE(ShortestEdgeRole).getShortestEdgeByIndex(index)->nodeIndex))
			    {
				    continue;
			    }
			}

			Node* node = graph.getNodeByIndex(index);
			Edge* edge = node->firstEdge;
			while(edge != NULL)
			{
				if(!ROLE(NodeMapRole).isNodeInBestGraph(edge->nodeIndex))
				{
					if(edge->weight < lowestWeight)
					{
						lowestWeight = edge->weight;
						bestEdge = edge;
					}
				}
				edge = edge->nextEdge;
			}
		}
		ROLE(ShortestEdgeRole).setShortestEdgeByIndex(index, bestEdge);
	}
}



