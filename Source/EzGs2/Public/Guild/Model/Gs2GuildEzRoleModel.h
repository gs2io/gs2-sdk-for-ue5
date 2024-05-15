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
#include "Guild/Model/RoleModel.h"

namespace Gs2::UE5::Guild::Model
{
	class EZGS2_API FEzRoleModel final : public TSharedFromThis<FEzRoleModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> PolicyDocumentValue;

	public:
        TSharedPtr<FEzRoleModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzRoleModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzRoleModel> WithPolicyDocument(const TOptional<FString> PolicyDocument);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetPolicyDocument() const;

        Gs2::Guild::Model::FRoleModelPtr ToModel() const;
        static TSharedPtr<FEzRoleModel> FromModel(Gs2::Guild::Model::FRoleModelPtr Model);
    };
    typedef TSharedPtr<FEzRoleModel> FEzRoleModelPtr;
}