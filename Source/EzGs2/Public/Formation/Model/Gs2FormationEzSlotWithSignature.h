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
#include "Formation/Model/SlotWithSignature.h"

namespace Gs2::UE5::Formation::Model
{
	class EZGS2_API FEzSlotWithSignature final : public TSharedFromThis<FEzSlotWithSignature>
	{
        TOptional<FString> NameValue;
        TOptional<FString> PropertyTypeValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        TOptional<FString> MetadataValue;

	public:
        TSharedPtr<FEzSlotWithSignature> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzSlotWithSignature> WithPropertyType(const TOptional<FString> PropertyType);
        TSharedPtr<FEzSlotWithSignature> WithBody(const TOptional<FString> Body);
        TSharedPtr<FEzSlotWithSignature> WithSignature(const TOptional<FString> Signature);
        TSharedPtr<FEzSlotWithSignature> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetName() const;

        TOptional<FString> GetPropertyType() const;

        TOptional<FString> GetBody() const;

        TOptional<FString> GetSignature() const;

        TOptional<FString> GetMetadata() const;

        Gs2::Formation::Model::FSlotWithSignaturePtr ToModel() const;
        static TSharedPtr<FEzSlotWithSignature> FromModel(Gs2::Formation::Model::FSlotWithSignaturePtr Model);
    };
    typedef TSharedPtr<FEzSlotWithSignature> FEzSlotWithSignaturePtr;
}