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
#include "Core/Gs2Object.h"

namespace Gs2::Lottery::Model
{
    class GS2LOTTERY_API FVerifyActionResult final : public FGs2Object, public TSharedFromThis<FVerifyActionResult>
    {
        TOptional<FString> ActionValue;
        TOptional<FString> VerifyRequestValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> VerifyResultValue;

    public:
        FVerifyActionResult();
        FVerifyActionResult(
            const FVerifyActionResult& From
        );
        virtual ~FVerifyActionResult() override = default;

        TSharedPtr<FVerifyActionResult> WithAction(const TOptional<FString> Action);
        TSharedPtr<FVerifyActionResult> WithVerifyRequest(const TOptional<FString> VerifyRequest);
        TSharedPtr<FVerifyActionResult> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FVerifyActionResult> WithVerifyResult(const TOptional<FString> VerifyResult);

        TOptional<FString> GetAction() const;
        TOptional<FString> GetVerifyRequest() const;
        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;
        TOptional<FString> GetVerifyResult() const;


        static TSharedPtr<FVerifyActionResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FVerifyActionResult, ESPMode::ThreadSafe> FVerifyActionResultPtr;
}