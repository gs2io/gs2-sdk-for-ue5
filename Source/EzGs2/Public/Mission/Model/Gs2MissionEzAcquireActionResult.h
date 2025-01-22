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
#include "Mission/Model/AcquireActionResult.h"

namespace Gs2::UE5::Mission::Model
{
	class EZGS2_API FEzAcquireActionResult final : public TSharedFromThis<FEzAcquireActionResult>
	{
        TOptional<FString> ActionValue;
        TOptional<FString> AcquireRequestValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> AcquireResultValue;

	public:
        TSharedPtr<FEzAcquireActionResult> WithAction(const TOptional<FString> Action);
        TSharedPtr<FEzAcquireActionResult> WithAcquireRequest(const TOptional<FString> AcquireRequest);
        TSharedPtr<FEzAcquireActionResult> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FEzAcquireActionResult> WithAcquireResult(const TOptional<FString> AcquireResult);

        TOptional<FString> GetAction() const;

        TOptional<FString> GetAcquireRequest() const;

        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;

        TOptional<FString> GetAcquireResult() const;

        Gs2::Mission::Model::FAcquireActionResultPtr ToModel() const;
        static TSharedPtr<FEzAcquireActionResult> FromModel(Gs2::Mission::Model::FAcquireActionResultPtr Model);
    };
    typedef TSharedPtr<FEzAcquireActionResult> FEzAcquireActionResultPtr;
}