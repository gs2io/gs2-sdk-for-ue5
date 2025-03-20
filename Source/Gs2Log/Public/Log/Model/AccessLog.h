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
    class GS2LOG_API FAccessLog final : public FGs2Object, public TSharedFromThis<FAccessLog>
    {
        TOptional<int64> TimestampValue;
        TOptional<FString> RequestIdValue;
        TOptional<FString> ServiceValue;
        TOptional<FString> MethodValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RequestValue;
        TOptional<FString> ResultValue;

    public:
        FAccessLog();
        FAccessLog(
            const FAccessLog& From
        );
        virtual ~FAccessLog() override = default;

        TSharedPtr<FAccessLog> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FAccessLog> WithRequestId(const TOptional<FString> RequestId);
        TSharedPtr<FAccessLog> WithService(const TOptional<FString> Service);
        TSharedPtr<FAccessLog> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FAccessLog> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAccessLog> WithRequest(const TOptional<FString> Request);
        TSharedPtr<FAccessLog> WithResult(const TOptional<FString> Result);

        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;
        TOptional<FString> GetRequestId() const;
        TOptional<FString> GetService() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRequest() const;
        TOptional<FString> GetResult() const;


        static TSharedPtr<FAccessLog> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAccessLog, ESPMode::ThreadSafe> FAccessLogPtr;
}