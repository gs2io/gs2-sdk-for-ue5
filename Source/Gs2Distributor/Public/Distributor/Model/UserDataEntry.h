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

namespace Gs2::Distributor::Model
{
    class GS2DISTRIBUTOR_API FUserDataEntry final : public FGs2Object, public TSharedFromThis<FUserDataEntry>
    {
        TOptional<FString> ServiceValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> KindValue;
        TOptional<FString> PayloadValue;

    public:
        FUserDataEntry();
        FUserDataEntry(
            const FUserDataEntry& From
        );
        virtual ~FUserDataEntry() override = default;

        TSharedPtr<FUserDataEntry> WithService(const TOptional<FString> Service);
        TSharedPtr<FUserDataEntry> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUserDataEntry> WithKind(const TOptional<FString> Kind);
        TSharedPtr<FUserDataEntry> WithPayload(const TOptional<FString> Payload);

        TOptional<FString> GetService() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetKind() const;
        TOptional<FString> GetPayload() const;


        static TSharedPtr<FUserDataEntry> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUserDataEntry, ESPMode::ThreadSafe> FUserDataEntryPtr;
}