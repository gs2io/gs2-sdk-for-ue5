#include "Core/EzAcquireActionResult.h"

namespace Gs2::UE5::Core::Model
{
	TSharedPtr<Gs2::UE5::Core::Model::FEzAcquireActionResult> FEzAcquireActionResult::WithAction(
		const TOptional<FString> Action
	)
	{
		this->ActionValue = Action;
		return SharedThis(this);
	}

	TSharedPtr<FEzAcquireActionResult> FEzAcquireActionResult::WithAcquireRequest(
		const TOptional<FString> AcquireRequest
	)
	{
		this->AcquireRequestValue = AcquireRequest;
		return SharedThis(this);
	}

	TSharedPtr<FEzAcquireActionResult> FEzAcquireActionResult::WithStatusCode(
		const TOptional<int32> StatusCode
	)
	{
		this->StatusCodeValue = StatusCode;
		return SharedThis(this);
	}

	TSharedPtr<FEzAcquireActionResult> FEzAcquireActionResult::WithAcquireResult(
		const TOptional<FString> AcquireResult
	)
	{
		this->AcquireResultValue = AcquireResult;
		return SharedThis(this);
	}

	TOptional<FString> FEzAcquireActionResult::GetAction() const
	{
		return ActionValue;
	}

	TOptional<FString> FEzAcquireActionResult::GetAcquireRequest() const
	{
		return AcquireRequestValue;
	}

	TOptional<int32> FEzAcquireActionResult::GetStatusCode() const
	{
		return StatusCodeValue;
	}

	TOptional<FString> FEzAcquireActionResult::GetAcquireResult() const
	{
		return AcquireResultValue;
	}

	Gs2::Core::Model::FAcquireActionResultPtr FEzAcquireActionResult::ToModel() const
	{
		return MakeShared<Gs2::Core::Model::FAcquireActionResult>()
			->WithAction(ActionValue)
			->WithAcquireRequest(AcquireRequestValue)
			->WithStatusCode(StatusCodeValue)
			->WithAcquireResult(AcquireResultValue);
	}

	TSharedPtr<FEzAcquireActionResult> FEzAcquireActionResult::FromModel(Gs2::Core::Model::FAcquireActionResultPtr Model)
	{
		return MakeShared<FEzAcquireActionResult>()
			->WithAction(Model->GetAction())
			->WithAcquireRequest(Model->GetAcquireRequest())
			->WithStatusCode(Model->GetStatusCode())
			->WithAcquireResult(Model->GetAcquireResult());
	}
}
