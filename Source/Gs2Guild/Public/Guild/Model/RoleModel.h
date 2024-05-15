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

namespace Gs2::Guild::Model
{
    class GS2GUILD_API FRoleModel final : public Gs2Object, public TSharedFromThis<FRoleModel>
    {
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> PolicyDocumentValue;

    public:
        FRoleModel();
        FRoleModel(
            const FRoleModel& From
        );
        virtual ~FRoleModel() override = default;

        TSharedPtr<FRoleModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FRoleModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRoleModel> WithPolicyDocument(const TOptional<FString> PolicyDocument);

        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetPolicyDocument() const;


        static TSharedPtr<FRoleModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRoleModel, ESPMode::ThreadSafe> FRoleModelPtr;
}