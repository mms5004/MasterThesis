// Include to access the TExecutableOperator class

#include "Misc/EngineVersionComparison.h"

#include "MetasoundDataReference.h"
#include "CoreMinimal.h"
#include "Internationalization/Text.h"
#include "MetasoundDataTypeRegistrationMacro.h"
#include "MetasoundVertex.h"
#include "MetasoundExecutableOperator.h"     // TExecutableOperator class
#include "MetasoundPrimitives.h"             // ReadRef and WriteRef descriptions for bool, int32, float, and string
#include "MetasoundNodeRegistrationMacro.h"  // METASOUND_LOCTEXT and METASOUND_REGISTER_NODE macros
#include "MetasoundStandardNodesNames.h"     // StandardNodes namespace
#include "MetasoundFacade.h"				 // FNodeFacade class, eliminates the need for a fair amount of boilerplate code
#include "MetasoundParamHelper.h"            // METASOUND_PARAM and METASOUND_GET_PARAM family of macros

#include "Misc/ScopeLock.h"
#include "AlphaParameters.h"
//TMap<FString, float> FAlphaParameters::AlphaMap;
//FCriticalSection FAlphaParameters::Mutex;


//Couldn't do it without :
//https://dev.epicgames.com/community/learning/tutorials/ry7p/unreal-engine-creating-metasound-nodes-in-c-quickstart
//https://github.com/gtreshchev/RuntimeAudioImporter/blob/main/Source/RuntimeAudioImporter/Private/MetaSound/MetasoundImportedWaveToWaveAssetNode.cpp
//Also metasound need to be called in module's plugin to register nodes

namespace Metasound
{
	// Required for ensuring the node is supported by all languages in engine. Must be unique per MetaSound.
	#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_MetaSoundMixerParameterNode"


	// Vertex Names - define your node's inputs and outputs here
	namespace MixerParameterNodeNames
	{
		METASOUND_PARAM(InputAValue, "A", "Alpha name");
		METASOUND_PARAM(InputBValue, "B", "Default value");
		METASOUND_PARAM(OutputValue, "Get Alpha Value", "Return 0 if not found");
	}


	// Operator Class - defines the way your node is described, created and executed
	class FMixerParameterOperator : public TExecutableOperator<FMixerParameterOperator>
	{
	public:
		// Constructor
		FMixerParameterOperator(
			const FStringReadRef& InAValue, const FFloatReadRef& InBValue)
			: InputA(InAValue), DefaultValue(InBValue)
			, MixerParameterOutput(FFloatWriteRef::CreateNew(0.0f))
		{
		}

		// Helper function for constructing vertex interface
		static const FVertexInterface& DeclareVertexInterface()
		{
			using namespace MixerParameterNodeNames;

			static const FVertexInterface Interface
			(
				FInputVertexInterface(
												TInputDataVertex<FString>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputAValue)),
												TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputBValue))
											 ),	
				FOutputVertexInterface(	TOutputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputValue)) )
			);
			return Interface;
		}

		// Retrieves necessary metadata about your node
		static const FNodeClassMetadata& GetNodeInfo()
		{
			auto CreateNodeClassMetadata = []() -> FNodeClassMetadata
				{
					FVertexInterface NodeInterface = DeclareVertexInterface();

					FText CategoryOne = FText::FromString("Mixer");
					FText CategoryTwo = FText::FromString("Parameter");

					FText KeywordOne = FText::FromString("Alpha");
					FText KeywordTwo = FText::FromString("RTPC");


					FNodeClassMetadata Metadata
					{
						FNodeClassName { TEXT("UE"), TEXT("Mixer Parameter Node"), TEXT("Audio")},
						1,
						0,
						METASOUND_LOCTEXT("NodeDisplayName", "Mixer Parameter Node"),
						METASOUND_LOCTEXT("NodeDescription", "Return an alpha parameter from mixer"),
						PluginAuthor,
						PluginNodeMissingPrompt,
						NodeInterface,
						{CategoryOne,CategoryTwo}, // Category Hierarchy 
						{KeywordOne, KeywordTwo}, // Keywords for searching
						FNodeDisplayStyle{}
					};

					return Metadata;
				};

			static const FNodeClassMetadata Metadata = CreateNodeClassMetadata();
			return Metadata;
		}

		// Allows MetaSound graph to interact with your node's inputs
		virtual FDataReferenceCollection GetInputs() const override
		{
			using namespace MixerParameterNodeNames;

			FDataReferenceCollection InputDataReferences;

			InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InputAValue), InputA);
			InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InputBValue), DefaultValue);

			return InputDataReferences;
		}

		// Allows MetaSound graph to interact with your node's outputs
		virtual FDataReferenceCollection GetOutputs() const override
		{
			using namespace MixerParameterNodeNames;

			FDataReferenceCollection OutputDataReferences;

			OutputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(OutputValue), MixerParameterOutput);

			return OutputDataReferences;
		}

		// Used to instantiate the runtime instance node
#if UE_VERSION_OLDER_THAN(5, 4, 0)
		static TUniquePtr<IOperator> CreateOperator(const Metasound::FCreateOperatorParams& InParams, Metasound::FBuildErrorArray& OutErrors)
		{
			using namespace MixerParameterNodeNames;

			const FDataReferenceCollection& InputDataRefs = InParams.InputDataReferences;

			FStringReadRef InputA = InputDataRefs.GetDataReadReferenceOrConstruct<FString>(METASOUND_GET_PARAM_NAME(InputAValue));
			FFloatReadRef InputA = InputDataRefs.GetDataReadReferenceOrConstruct<floatf>(METASOUND_GET_PARAM_NAME(InputBValue));

			return MakeUnique<FMixerParameterOperator>(InputA, InputB);
		}
#else
		static TUniquePtr<IOperator> CreateOperator(const Metasound::FBuildOperatorParams& InParams, Metasound::FBuildResults& OutResults)
		{
			using namespace MixerParameterNodeNames;

			const FInputVertexInterfaceData& InputDataRefs = InParams.InputData;

			FStringReadRef InputA = InputDataRefs.GetOrCreateDefaultDataReadReference<FString>(METASOUND_GET_PARAM_NAME(InputAValue), InParams.OperatorSettings);
			FFloatReadRef InputB = InputDataRefs.GetOrCreateDefaultDataReadReference<float>(METASOUND_GET_PARAM_NAME(InputBValue), InParams.OperatorSettings);

			return MakeUnique<FMixerParameterOperator>(InputA, InputB);
		}
#endif


		void Execute()
		{
			*MixerParameterOutput = FAlphaParameters::Get(*InputA, *DefaultValue);
		}

	private:

		// Inputs
		FStringReadRef InputA;
		FFloatReadRef DefaultValue;

		// Outputs
		FFloatWriteRef MixerParameterOutput;
	};

	// Node Class - Inheriting from FNodeFacade is recommended for nodes that have a static FVertexInterface
	class FMixerParameterNode : public FNodeFacade
	{
	public:
		FMixerParameterNode(const FNodeInitData& InitData)
			: FNodeFacade(InitData.InstanceName, InitData.InstanceID, TFacadeOperatorClass<FMixerParameterOperator>())
		{
		}
	};

	// Register node
	METASOUND_REGISTER_NODE(FMixerParameterNode);
}

#undef LOCTEXT_NAMESPACE