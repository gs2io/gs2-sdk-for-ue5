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
#include "TransactionSetting.h"
#include "ScriptSetting.h"
#include "LogSetting.h"

namespace Gs2::StateMachine::Model
{
    class GS2STATEMACHINE_API FNamespace final : public Gs2Object, public TSharedFromThis<FNamespace>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> SupportSpeculativeExecutionValue;
        TSharedPtr<FTransactionSetting> TransactionSettingValue;
        TSharedPtr<FScriptSetting> StartScriptValue;
        TSharedPtr<FScriptSetting> PassScriptValue;
        TSharedPtr<FScriptSetting> ErrorScriptValue;
        TOptional<int64> LowestStateMachineVersionValue;
        TSharedPtr<FLogSetting> LogSettingValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FNamespace();
        FNamespace(
            const FNamespace& From
        );
        virtual ~FNamespace() override = default;

        TSharedPtr<FNamespace> WithNamespaceId(const TOptional<FString> NamespaceId);
        TSharedPtr<FNamespace> WithName(const TOptional<FString> Name);
        TSharedPtr<FNamespace> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FNamespace> WithSupportSpeculativeExecution(const TOptional<FString> SupportSpeculativeExecution);
        TSharedPtr<FNamespace> WithTransactionSetting(const TSharedPtr<FTransactionSetting> TransactionSetting);
        TSharedPtr<FNamespace> WithStartScript(const TSharedPtr<FScriptSetting> StartScript);
        TSharedPtr<FNamespace> WithPassScript(const TSharedPtr<FScriptSetting> PassScript);
        TSharedPtr<FNamespace> WithErrorScript(const TSharedPtr<FScriptSetting> ErrorScript);
        TSharedPtr<FNamespace> WithLowestStateMachineVersion(const TOptional<int64> LowestStateMachineVersion);
        TSharedPtr<FNamespace> WithLogSetting(const TSharedPtr<FLogSetting> LogSetting);
        TSharedPtr<FNamespace> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FNamespace> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FNamespace> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetSupportSpeculativeExecution() const;
        TSharedPtr<FTransactionSetting> GetTransactionSetting() const;
        TSharedPtr<FScriptSetting> GetStartScript() const;
        TSharedPtr<FScriptSetting> GetPassScript() const;
        TSharedPtr<FScriptSetting> GetErrorScript() const;
        TOptional<int64> GetLowestStateMachineVersion() const;
        FString GetLowestStateMachineVersionString() const;
        TSharedPtr<FLogSetting> GetLogSetting() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);

        static TSharedPtr<FNamespace> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FNamespace, ESPMode::ThreadSafe> FNamespacePtr;
}