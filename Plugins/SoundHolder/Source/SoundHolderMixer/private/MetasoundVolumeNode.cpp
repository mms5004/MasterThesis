// Copyright Epic Games, Inc. All Rights Reserved.

#include "MetasoundVolumeNode.h"

#include "MetasoundNodeRegistrationMacro.h"

#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_ValueConnard"

namespace Metasound
{
	namespace MetasoundValueNodePrivate
	{
		FNodeClassMetadata CreateNodeClassMetadata(const FName& InDataTypeName, const FName& InOperatorName, const FText& InDisplayName, const FText& InDescription, const FVertexInterface& InDefaultInterface)
		{
			FNodeClassMetadata Metadata
			{
				FNodeClassName{ "CONNARD?", InOperatorName, InDataTypeName },
				1, // Major Version
				0, // Minor Version
				InDisplayName,
				InDescription,
				PluginAuthor,
				PluginNodeMissingPrompt,
				InDefaultInterface,
				{ METASOUND_LOCTEXT("ValueCategory", "connard") },
				{ },
				FNodeDisplayStyle{}
			};

			return Metadata;
		}
	}


	using FValueNodeInt32 = TValueNode<int32>;
	METASOUND_REGISTER_NODE(FValueNodeInt32)

		using FValueNodeFloat = TValueNode<float>;
	METASOUND_REGISTER_NODE(FValueNodeFloat)

		using FValueNodeBool = TValueNode<bool>;
	METASOUND_REGISTER_NODE(FValueNodeBool)

		using FValueNodeString = TValueNode<FString>;
	METASOUND_REGISTER_NODE(FValueNodeString)
}

#undef LOCTEXT_NAMESPACE