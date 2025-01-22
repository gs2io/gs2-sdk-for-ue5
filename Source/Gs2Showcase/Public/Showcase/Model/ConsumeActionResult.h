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

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FConsumeActionResult final : public Gs2Object, public TSharedFromThis<FConsumeActionResult>
    {
        TOptional<FString> ActionValue;
        TOptional<FString> ConsumeRequestValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> ConsumeResultValue;

    public:
        FConsumeActionResult();
        FConsumeActionResult(
            const FConsumeActionResult& From
        );
        virtual ~FConsumeActionResult() override = default;

        TSharedPtr<FConsumeActionResult> WithAction(const TOptional<FString> Action);
        TSharedPtr<FConsumeActionResult> WithConsumeRequest(const TOptional<FString> ConsumeRequest);
        TSharedPtr<FConsumeActionResult> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FConsumeActionResult> WithConsumeResult(const TOptional<FString> ConsumeResult);

        TOptional<FString> GetAction() const;
        TOptional<FString> GetConsumeRequest() const;
        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;
        TOptional<FString> GetConsumeResult() const;


        static TSharedPtr<FConsumeActionResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FConsumeActionResult, ESPMode::ThreadSafe> FConsumeActionResultPtr;
}