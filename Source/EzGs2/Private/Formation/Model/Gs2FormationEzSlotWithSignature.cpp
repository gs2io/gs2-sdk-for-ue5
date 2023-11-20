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

#include "Formation/Model/Gs2FormationEzSlotWithSignature.h"

namespace Gs2::UE5::Formation::Model
{

    TSharedPtr<FEzSlotWithSignature> FEzSlotWithSignature::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzSlotWithSignature> FEzSlotWithSignature::WithPropertyType(
        const TOptional<FString> PropertyType
    )
    {
        this->PropertyTypeValue = PropertyType;
        return SharedThis(this);
    }

    TSharedPtr<FEzSlotWithSignature> FEzSlotWithSignature::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FEzSlotWithSignature> FEzSlotWithSignature::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TSharedPtr<FEzSlotWithSignature> FEzSlotWithSignature::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }
    TOptional<FString> FEzSlotWithSignature::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzSlotWithSignature::GetPropertyType() const
    {
        return PropertyTypeValue;
    }
    TOptional<FString> FEzSlotWithSignature::GetBody() const
    {
        return BodyValue;
    }
    TOptional<FString> FEzSlotWithSignature::GetSignature() const
    {
        return SignatureValue;
    }
    TOptional<FString> FEzSlotWithSignature::GetMetadata() const
    {
        return MetadataValue;
    }

    Gs2::Formation::Model::FSlotWithSignaturePtr FEzSlotWithSignature::ToModel() const
    {
        return MakeShared<Gs2::Formation::Model::FSlotWithSignature>()
            ->WithName(NameValue)
            ->WithPropertyType(PropertyTypeValue)
            ->WithBody(BodyValue)
            ->WithSignature(SignatureValue)
            ->WithMetadata(MetadataValue);
    }

    TSharedPtr<FEzSlotWithSignature> FEzSlotWithSignature::FromModel(const Gs2::Formation::Model::FSlotWithSignaturePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSlotWithSignature>()
            ->WithName(Model->GetName())
            ->WithPropertyType(Model->GetPropertyType())
            ->WithBody(Model->GetBody())
            ->WithSignature(Model->GetSignature())
            ->WithMetadata(Model->GetMetadata());
    }
}