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

#include "Formation/Model/SlotWithSignature.h"

namespace Gs2::Formation::Model
{
    FSlotWithSignature::FSlotWithSignature():
        NameValue(TOptional<FString>()),
        PropertyTypeValue(TOptional<FString>()),
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>())
    {
    }

    FSlotWithSignature::FSlotWithSignature(
        const FSlotWithSignature& From
    ):
        NameValue(From.NameValue),
        PropertyTypeValue(From.PropertyTypeValue),
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue),
        MetadataValue(From.MetadataValue)
    {
    }

    TSharedPtr<FSlotWithSignature> FSlotWithSignature::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FSlotWithSignature> FSlotWithSignature::WithPropertyType(
        const TOptional<FString> PropertyType
    )
    {
        this->PropertyTypeValue = PropertyType;
        return SharedThis(this);
    }

    TSharedPtr<FSlotWithSignature> FSlotWithSignature::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FSlotWithSignature> FSlotWithSignature::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TSharedPtr<FSlotWithSignature> FSlotWithSignature::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }
    TOptional<FString> FSlotWithSignature::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FSlotWithSignature::GetPropertyType() const
    {
        return PropertyTypeValue;
    }
    TOptional<FString> FSlotWithSignature::GetBody() const
    {
        return BodyValue;
    }
    TOptional<FString> FSlotWithSignature::GetSignature() const
    {
        return SignatureValue;
    }
    TOptional<FString> FSlotWithSignature::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<FSlotWithSignature> FSlotWithSignature::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSlotWithSignature>()
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPropertyType(Data->HasField("propertyType") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("propertyType", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBody(Data->HasField("body") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("body", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSignature(Data->HasField("signature") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("signature", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSlotWithSignature::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (PropertyTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyType", PropertyTypeValue.GetValue());
        }
        if (BodyValue.IsSet())
        {
            JsonRootObject->SetStringField("body", BodyValue.GetValue());
        }
        if (SignatureValue.IsSet())
        {
            JsonRootObject->SetStringField("signature", SignatureValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FSlotWithSignature::TypeName = "SlotWithSignature";
}