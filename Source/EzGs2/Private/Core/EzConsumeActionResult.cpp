#include "Core/EzConsumeActionResult.h"

namespace Gs2::UE5::Core::Model
{
	TSharedPtr<Gs2::UE5::Core::Model::FEzConsumeActionResult> FEzConsumeActionResult::WithAction(
		const TOptional<FString> Action
	)
	{
		this->ActionValue = Action;
		return SharedThis(this);
	}

	TSharedPtr<FEzConsumeActionResult> FEzConsumeActionResult::WithConsumeRequest(
		const TOptional<FString> ConsumeRequest
	)
	{
		this->ConsumeRequestValue = ConsumeRequest;
		return SharedThis(this);
	}

	TSharedPtr<FEzConsumeActionResult> FEzConsumeActionResult::WithStatusCode(
		const TOptional<int32> StatusCode
	)
	{
		this->StatusCodeValue = StatusCode;
		return SharedThis(this);
	}

	TSharedPtr<FEzConsumeActionResult> FEzConsumeActionResult::WithConsumeResult(
		const TOptional<FString> ConsumeResult
	)
	{
		this->ConsumeResultValue = ConsumeResult;
		return SharedThis(this);
	}

	TOptional<FString> FEzConsumeActionResult::GetAction() const
	{
		return ActionValue;
	}

	TOptional<FString> FEzConsumeActionResult::GetConsumeRequest() const
	{
		return ConsumeRequestValue;
	}

	TOptional<int32> FEzConsumeActionResult::GetStatusCode() const
	{
		return StatusCodeValue;
	}

	TOptional<FString> FEzConsumeActionResult::GetConsumeResult() const
	{
		return ConsumeResultValue;
	}

	Gs2::Core::Model::FConsumeActionResultPtr FEzConsumeActionResult::ToModel() const
	{
		return MakeShared<Gs2::Core::Model::FConsumeActionResult>()
			->WithAction(ActionValue)
			->WithConsumeRequest(ConsumeRequestValue)
			->WithStatusCode(StatusCodeValue)
			->WithConsumeResult(ConsumeResultValue);
	}

	TSharedPtr<FEzConsumeActionResult> FEzConsumeActionResult::FromModel(Gs2::Core::Model::FConsumeActionResultPtr Model)
	{
		return MakeShared<FEzConsumeActionResult>()
			->WithAction(Model->GetAction())
			->WithConsumeRequest(Model->GetConsumeRequest())
			->WithStatusCode(Model->GetStatusCode())
			->WithConsumeResult(Model->GetConsumeResult());
	}
}
