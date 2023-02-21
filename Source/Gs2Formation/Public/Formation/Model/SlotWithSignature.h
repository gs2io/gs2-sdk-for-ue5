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

namespace Gs2::Formation::Model
{
    class GS2FORMATION_API FSlotWithSignature final : public TSharedFromThis<FSlotWithSignature>
    {
        TOptional<FString> NameValue;
        TOptional<FString> PropertyTypeValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        TOptional<FString> MetadataValue;

    public:
        FSlotWithSignature();
        FSlotWithSignature(
            const FSlotWithSignature& From
        );
        ~FSlotWithSignature() = default;

        TSharedPtr<FSlotWithSignature> WithName(const TOptional<FString> Name);
        TSharedPtr<FSlotWithSignature> WithPropertyType(const TOptional<FString> PropertyType);
        TSharedPtr<FSlotWithSignature> WithBody(const TOptional<FString> Body);
        TSharedPtr<FSlotWithSignature> WithSignature(const TOptional<FString> Signature);
        TSharedPtr<FSlotWithSignature> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetName() const;
        TOptional<FString> GetPropertyType() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;
        TOptional<FString> GetMetadata() const;


        static TSharedPtr<FSlotWithSignature> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSlotWithSignature, ESPMode::ThreadSafe> FSlotWithSignaturePtr;
}