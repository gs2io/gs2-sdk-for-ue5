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

namespace Gs2::JobQueue::Model
{
    class GS2JOBQUEUE_API FJobResultBody final : public Gs2Object, public TSharedFromThis<FJobResultBody>
    {
        TOptional<int32> TryNumberValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> ResultValue;
        TOptional<int64> TryAtValue;

    public:
        FJobResultBody();
        FJobResultBody(
            const FJobResultBody& From
        );
        virtual ~FJobResultBody() override = default;

        TSharedPtr<FJobResultBody> WithTryNumber(const TOptional<int32> TryNumber);
        TSharedPtr<FJobResultBody> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FJobResultBody> WithResult(const TOptional<FString> Result);
        TSharedPtr<FJobResultBody> WithTryAt(const TOptional<int64> TryAt);

        TOptional<int32> GetTryNumber() const;
        FString GetTryNumberString() const;
        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;
        TOptional<FString> GetResult() const;
        TOptional<int64> GetTryAt() const;
        FString GetTryAtString() const;


        static TSharedPtr<FJobResultBody> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FJobResultBody, ESPMode::ThreadSafe> FJobResultBodyPtr;
}