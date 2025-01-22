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
#include "Ranking2/Model/VerifyActionResult.h"

namespace Gs2::UE5::Ranking2::Model
{
	class EZGS2_API FEzVerifyActionResult final : public TSharedFromThis<FEzVerifyActionResult>
	{
        TOptional<FString> ActionValue;
        TOptional<FString> VerifyRequestValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> VerifyResultValue;

	public:
        TSharedPtr<FEzVerifyActionResult> WithAction(const TOptional<FString> Action);
        TSharedPtr<FEzVerifyActionResult> WithVerifyRequest(const TOptional<FString> VerifyRequest);
        TSharedPtr<FEzVerifyActionResult> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FEzVerifyActionResult> WithVerifyResult(const TOptional<FString> VerifyResult);

        TOptional<FString> GetAction() const;

        TOptional<FString> GetVerifyRequest() const;

        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;

        TOptional<FString> GetVerifyResult() const;

        Gs2::Ranking2::Model::FVerifyActionResultPtr ToModel() const;
        static TSharedPtr<FEzVerifyActionResult> FromModel(Gs2::Ranking2::Model::FVerifyActionResultPtr Model);
    };
    typedef TSharedPtr<FEzVerifyActionResult> FEzVerifyActionResultPtr;
}