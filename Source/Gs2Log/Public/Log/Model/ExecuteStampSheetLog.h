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
    class GS2LOG_API FExecuteStampSheetLog final : public Gs2Object, public TSharedFromThis<FExecuteStampSheetLog>
    {
        TOptional<int64> TimestampValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> ServiceValue;
        TOptional<FString> MethodValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ActionValue;
        TOptional<FString> ArgsValue;

    public:
        FExecuteStampSheetLog();
        FExecuteStampSheetLog(
            const FExecuteStampSheetLog& From
        );
        virtual ~FExecuteStampSheetLog() override = default;

        TSharedPtr<FExecuteStampSheetLog> WithTimestamp(const TOptional<int64> Timestamp);
        TSharedPtr<FExecuteStampSheetLog> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FExecuteStampSheetLog> WithService(const TOptional<FString> Service);
        TSharedPtr<FExecuteStampSheetLog> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FExecuteStampSheetLog> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FExecuteStampSheetLog> WithAction(const TOptional<FString> Action);
        TSharedPtr<FExecuteStampSheetLog> WithArgs(const TOptional<FString> Args);

        TOptional<int64> GetTimestamp() const;
        FString GetTimestampString() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetService() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAction() const;
        TOptional<FString> GetArgs() const;


        static TSharedPtr<FExecuteStampSheetLog> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FExecuteStampSheetLog, ESPMode::ThreadSafe> FExecuteStampSheetLogPtr;
}