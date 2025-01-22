/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "Experience/Model/ConsumeActionResult.h"

namespace Gs2::UE5::Experience::Model
{
	class EZGS2_API FEzConsumeActionResult final : public TSharedFromThis<FEzConsumeActionResult>
	{
        TOptional<FString> ActionValue;
        TOptional<FString> ConsumeRequestValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> ConsumeResultValue;

	public:
        TSharedPtr<FEzConsumeActionResult> WithAction(const TOptional<FString> Action);
        TSharedPtr<FEzConsumeActionResult> WithConsumeRequest(const TOptional<FString> ConsumeRequest);
        TSharedPtr<FEzConsumeActionResult> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FEzConsumeActionResult> WithConsumeResult(const TOptional<FString> ConsumeResult);

        TOptional<FString> GetAction() const;

        TOptional<FString> GetConsumeRequest() const;

        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;

        TOptional<FString> GetConsumeResult() const;

        Gs2::Experience::Model::FConsumeActionResultPtr ToModel() const;
        static TSharedPtr<FEzConsumeActionResult> FromModel(Gs2::Experience::Model::FConsumeActionResultPtr Model);
    };
    typedef TSharedPtr<FEzConsumeActionResult> FEzConsumeActionResultPtr;
}