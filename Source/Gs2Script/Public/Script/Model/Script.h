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

namespace Gs2::Script::Model
{
    class GS2SCRIPT_API FScript final : public FGs2Object, public TSharedFromThis<FScript>
    {
        TOptional<FString> ScriptIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ScriptValue;
        TOptional<bool> DisableStringNumberToNumberValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FScript();
        FScript(
            const FScript& From
        );
        virtual ~FScript() override = default;

        TSharedPtr<FScript> WithScriptId(const TOptional<FString> ScriptId);
        TSharedPtr<FScript> WithName(const TOptional<FString> Name);
        TSharedPtr<FScript> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FScript> WithScript(const TOptional<FString> Script);
        TSharedPtr<FScript> WithDisableStringNumberToNumber(const TOptional<bool> DisableStringNumberToNumber);
        TSharedPtr<FScript> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FScript> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FScript> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetScriptId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetScript() const;
        TOptional<bool> GetDisableStringNumberToNumber() const;
        FString GetDisableStringNumberToNumberString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetScriptNameFromGrn(const FString Grn);

        static TSharedPtr<FScript> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FScript, ESPMode::ThreadSafe> FScriptPtr;
}