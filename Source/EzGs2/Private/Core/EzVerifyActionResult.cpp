#include "Core/EzVerifyActionResult.h"

namespace Gs2::UE5::Core::Model
{
	TSharedPtr<Gs2::UE5::Core::Model::FEzVerifyActionResult> FEzVerifyActionResult::WithAction(
		const TOptional<FString> Action
	)
	{
		this->ActionValue = Action;
		return SharedThis(this);
	}

	TSharedPtr<FEzVerifyActionResult> FEzVerifyActionResult::WithVerifyRequest(
		const TOptional<FString> VerifyRequest
	)
	{
		this->VerifyRequestValue = VerifyRequest;
		return SharedThis(this);
	}

	TSharedPtr<FEzVerifyActionResult> FEzVerifyActionResult::WithStatusCode(
		const TOptional<int32> StatusCode
	)
	{
		this->StatusCodeValue = StatusCode;
		return SharedThis(this);
	}

	TSharedPtr<FEzVerifyActionResult> FEzVerifyActionResult::WithVerifyResult(
		const TOptional<FString> VerifyResult
	)
	{
		this->VerifyResultValue = VerifyResult;
		return SharedThis(this);
	}

	TOptional<FString> FEzVerifyActionResult::GetAction() const
	{
		return ActionValue;
	}

	TOptional<FString> FEzVerifyActionResult::GetVerifyRequest() const
	{
		return VerifyRequestValue;
	}

	TOptional<int32> FEzVerifyActionResult::GetStatusCode() const
	{
		return StatusCodeValue;
	}

	TOptional<FString> FEzVerifyActionResult::GetVerifyResult() const
	{
		return VerifyResultValue;
	}

	Gs2::Core::Model::FVerifyActionResultPtr FEzVerifyActionResult::ToModel() const
	{
		return MakeShared<Gs2::Core::Model::FVerifyActionResult>()
			->WithAction(ActionValue)
			->WithVerifyRequest(VerifyRequestValue)
			->WithStatusCode(StatusCodeValue)
			->WithVerifyResult(VerifyResultValue);
	}

	TSharedPtr<FEzVerifyActionResult> FEzVerifyActionResult::FromModel(Gs2::Core::Model::FVerifyActionResultPtr Model)
	{
		return MakeShared<FEzVerifyActionResult>()
			->WithAction(Model->GetAction())
			->WithVerifyRequest(Model->GetVerifyRequest())
			->WithStatusCode(Model->GetStatusCode())
			->WithVerifyResult(Model->GetVerifyResult());
	}
}
