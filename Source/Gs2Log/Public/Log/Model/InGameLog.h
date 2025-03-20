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
#include "InGameLogTag.h"

namespace Gs2::Log::Model
{
    class GS2LOG_API FInGameLog final : public FGs2Object, public TSharedFromThis<FInGameLog>
    {
        TOptional<int64> TimestampValue;
        TOptional<FString> RequestIdValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<FInGameLogTag>>> TagsValue;
        TOptional<FString> PayloadValue;

    public:
        FInGameLog();
        FInGameLog(
            const FInGameLog& From
        );
        virtual ~FInGameLog() override = default;

        TSharedPtr<FInGameLog> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FInGameLog> WithRequestId(const TOptional<FString> RequestId);
        TSharedPtr<FInGameLog> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FInGameLog> WithTags(const TSharedPtr<TArray<TSharedPtr<FInGameLogTag>>> Tags);
        TSharedPtr<FInGameLog> WithPayload(const TOptional<FString> Payload);

        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;
        TOptional<FString> GetRequestId() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<TSharedPtr<FInGameLogTag>>> GetTags() const;
        TOptional<FString> GetPayload() const;


        static TSharedPtr<FInGameLog> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FInGameLog, ESPMode::ThreadSafe> FInGameLogPtr;
}