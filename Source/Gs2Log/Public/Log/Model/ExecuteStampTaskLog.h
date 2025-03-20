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
    class GS2LOG_API FExecuteStampTaskLog final : public FGs2Object, public TSharedFromThis<FExecuteStampTaskLog>
    {
        TOptional<int64> TimestampValue;
        TOptional<FString> TaskIdValue;
        TOptional<FString> ServiceValue;
        TOptional<FString> MethodValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ActionValue;
        TOptional<FString> ArgsValue;

    public:
        FExecuteStampTaskLog();
        FExecuteStampTaskLog(
            const FExecuteStampTaskLog& From
        );
        virtual ~FExecuteStampTaskLog() override = default;

        TSharedPtr<FExecuteStampTaskLog> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FExecuteStampTaskLog> WithTaskId(const TOptional<FString> TaskId);
        TSharedPtr<FExecuteStampTaskLog> WithService(const TOptional<FString> Service);
        TSharedPtr<FExecuteStampTaskLog> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FExecuteStampTaskLog> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FExecuteStampTaskLog> WithAction(const TOptional<FString> Action);
        TSharedPtr<FExecuteStampTaskLog> WithArgs(const TOptional<FString> Args);

        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;
        TOptional<FString> GetTaskId() const;
        TOptional<FString> GetService() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAction() const;
        TOptional<FString> GetArgs() const;


        static TSharedPtr<FExecuteStampTaskLog> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FExecuteStampTaskLog, ESPMode::ThreadSafe> FExecuteStampTaskLogPtr;
}