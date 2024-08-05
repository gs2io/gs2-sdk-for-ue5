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
    class GS2LOG_API FExecuteStampSheetLogCount final : public Gs2Object, public TSharedFromThis<FExecuteStampSheetLogCount>
    {
        TOptional<FString> ServiceValue;
        TOptional<FString> MethodValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ActionValue;
        TOptional<int64> CountValue;

    public:
        FExecuteStampSheetLogCount();
        FExecuteStampSheetLogCount(
            const FExecuteStampSheetLogCount& From
        );
        virtual ~FExecuteStampSheetLogCount() override = default;

        TSharedPtr<FExecuteStampSheetLogCount> WithService(const TOptional<FString> Service);
        TSharedPtr<FExecuteStampSheetLogCount> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FExecuteStampSheetLogCount> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FExecuteStampSheetLogCount> WithAction(const TOptional<FString> Action);
        TSharedPtr<FExecuteStampSheetLogCount> WithCount(const TOptional<int64> Count);

        TOptional<FString> GetService() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAction() const;
        TOptional<int64> GetCount() const;
        FString GetCountString() const;


        static TSharedPtr<FExecuteStampSheetLogCount> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FExecuteStampSheetLogCount, ESPMode::ThreadSafe> FExecuteStampSheetLogCountPtr;
}