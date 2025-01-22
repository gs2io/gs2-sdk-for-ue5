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

namespace Gs2::Experience::Model
{
    class GS2EXPERIENCE_API FAcquireActionResult final : public Gs2Object, public TSharedFromThis<FAcquireActionResult>
    {
        TOptional<FString> ActionValue;
        TOptional<FString> AcquireRequestValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> AcquireResultValue;

    public:
        FAcquireActionResult();
        FAcquireActionResult(
            const FAcquireActionResult& From
        );
        virtual ~FAcquireActionResult() override = default;

        TSharedPtr<FAcquireActionResult> WithAction(const TOptional<FString> Action);
        TSharedPtr<FAcquireActionResult> WithAcquireRequest(const TOptional<FString> AcquireRequest);
        TSharedPtr<FAcquireActionResult> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FAcquireActionResult> WithAcquireResult(const TOptional<FString> AcquireResult);

        TOptional<FString> GetAction() const;
        TOptional<FString> GetAcquireRequest() const;
        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;
        TOptional<FString> GetAcquireResult() const;


        static TSharedPtr<FAcquireActionResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAcquireActionResult, ESPMode::ThreadSafe> FAcquireActionResultPtr;
}