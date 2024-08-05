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

namespace Gs2::Log::Model
{
    class GS2LOG_API FAccessLogCount final : public Gs2Object, public TSharedFromThis<FAccessLogCount>
    {
        TOptional<FString> ServiceValue;
        TOptional<FString> MethodValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> CountValue;

    public:
        FAccessLogCount();
        FAccessLogCount(
            const FAccessLogCount& From
        );
        virtual ~FAccessLogCount() override = default;

        TSharedPtr<FAccessLogCount> WithService(const TOptional<FString> Service);
        TSharedPtr<FAccessLogCount> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FAccessLogCount> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAccessLogCount> WithCount(const TOptional<int64> Count);

        TOptional<FString> GetService() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetCount() const;
        FString GetCountString() const;


        static TSharedPtr<FAccessLogCount> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAccessLogCount, ESPMode::ThreadSafe> FAccessLogCountPtr;
}