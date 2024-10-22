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

#include "Guard/Model/BlockingPolicyModel.h"

namespace Gs2::Guard::Model
{
    FBlockingPolicyModel::FBlockingPolicyModel():
        PassServicesValue(nullptr),
        DefaultRestrictionValue(TOptional<FString>()),
        LocationDetectionValue(TOptional<FString>()),
        LocationsValue(nullptr),
        LocationRestrictionValue(TOptional<FString>()),
        AnonymousIpDetectionValue(TOptional<FString>()),
        AnonymousIpRestrictionValue(TOptional<FString>()),
        HostingProviderIpDetectionValue(TOptional<FString>()),
        HostingProviderIpRestrictionValue(TOptional<FString>()),
        ReputationIpDetectionValue(TOptional<FString>()),
        ReputationIpRestrictionValue(TOptional<FString>()),
        IpAddressesDetectionValue(TOptional<FString>()),
        IpAddressesValue(nullptr),
        IpAddressRestrictionValue(TOptional<FString>())
    {
    }

    FBlockingPolicyModel::FBlockingPolicyModel(
        const FBlockingPolicyModel& From
    ):
        PassServicesValue(From.PassServicesValue),
        DefaultRestrictionValue(From.DefaultRestrictionValue),
        LocationDetectionValue(From.LocationDetectionValue),
        LocationsValue(From.LocationsValue),
        LocationRestrictionValue(From.LocationRestrictionValue),
        AnonymousIpDetectionValue(From.AnonymousIpDetectionValue),
        AnonymousIpRestrictionValue(From.AnonymousIpRestrictionValue),
        HostingProviderIpDetectionValue(From.HostingProviderIpDetectionValue),
        HostingProviderIpRestrictionValue(From.HostingProviderIpRestrictionValue),
        ReputationIpDetectionValue(From.ReputationIpDetectionValue),
        ReputationIpRestrictionValue(From.ReputationIpRestrictionValue),
        IpAddressesDetectionValue(From.IpAddressesDetectionValue),
        IpAddressesValue(From.IpAddressesValue),
        IpAddressRestrictionValue(From.IpAddressRestrictionValue)
    {
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithPassServices(
        const TSharedPtr<TArray<FString>> PassServices
    )
    {
        this->PassServicesValue = PassServices;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithDefaultRestriction(
        const TOptional<FString> DefaultRestriction
    )
    {
        this->DefaultRestrictionValue = DefaultRestriction;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithLocationDetection(
        const TOptional<FString> LocationDetection
    )
    {
        this->LocationDetectionValue = LocationDetection;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithLocations(
        const TSharedPtr<TArray<FString>> Locations
    )
    {
        this->LocationsValue = Locations;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithLocationRestriction(
        const TOptional<FString> LocationRestriction
    )
    {
        this->LocationRestrictionValue = LocationRestriction;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithAnonymousIpDetection(
        const TOptional<FString> AnonymousIpDetection
    )
    {
        this->AnonymousIpDetectionValue = AnonymousIpDetection;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithAnonymousIpRestriction(
        const TOptional<FString> AnonymousIpRestriction
    )
    {
        this->AnonymousIpRestrictionValue = AnonymousIpRestriction;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithHostingProviderIpDetection(
        const TOptional<FString> HostingProviderIpDetection
    )
    {
        this->HostingProviderIpDetectionValue = HostingProviderIpDetection;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithHostingProviderIpRestriction(
        const TOptional<FString> HostingProviderIpRestriction
    )
    {
        this->HostingProviderIpRestrictionValue = HostingProviderIpRestriction;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithReputationIpDetection(
        const TOptional<FString> ReputationIpDetection
    )
    {
        this->ReputationIpDetectionValue = ReputationIpDetection;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithReputationIpRestriction(
        const TOptional<FString> ReputationIpRestriction
    )
    {
        this->ReputationIpRestrictionValue = ReputationIpRestriction;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithIpAddressesDetection(
        const TOptional<FString> IpAddressesDetection
    )
    {
        this->IpAddressesDetectionValue = IpAddressesDetection;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithIpAddresses(
        const TSharedPtr<TArray<FString>> IpAddresses
    )
    {
        this->IpAddressesValue = IpAddresses;
        return SharedThis(this);
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::WithIpAddressRestriction(
        const TOptional<FString> IpAddressRestriction
    )
    {
        this->IpAddressRestrictionValue = IpAddressRestriction;
        return SharedThis(this);
    }
    TSharedPtr<TArray<FString>> FBlockingPolicyModel::GetPassServices() const
    {
        return PassServicesValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetDefaultRestriction() const
    {
        return DefaultRestrictionValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetLocationDetection() const
    {
        return LocationDetectionValue;
    }
    TSharedPtr<TArray<FString>> FBlockingPolicyModel::GetLocations() const
    {
        return LocationsValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetLocationRestriction() const
    {
        return LocationRestrictionValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetAnonymousIpDetection() const
    {
        return AnonymousIpDetectionValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetAnonymousIpRestriction() const
    {
        return AnonymousIpRestrictionValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetHostingProviderIpDetection() const
    {
        return HostingProviderIpDetectionValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetHostingProviderIpRestriction() const
    {
        return HostingProviderIpRestrictionValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetReputationIpDetection() const
    {
        return ReputationIpDetectionValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetReputationIpRestriction() const
    {
        return ReputationIpRestrictionValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetIpAddressesDetection() const
    {
        return IpAddressesDetectionValue;
    }
    TSharedPtr<TArray<FString>> FBlockingPolicyModel::GetIpAddresses() const
    {
        return IpAddressesValue;
    }
    TOptional<FString> FBlockingPolicyModel::GetIpAddressRestriction() const
    {
        return IpAddressRestrictionValue;
    }

    TSharedPtr<FBlockingPolicyModel> FBlockingPolicyModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBlockingPolicyModel>()
            ->WithPassServices(Data->HasField(ANSI_TO_TCHAR("passServices")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("passServices")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("passServices")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("passServices")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithDefaultRestriction(Data->HasField(ANSI_TO_TCHAR("defaultRestriction")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("defaultRestriction"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLocationDetection(Data->HasField(ANSI_TO_TCHAR("locationDetection")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("locationDetection"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLocations(Data->HasField(ANSI_TO_TCHAR("locations")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("locations")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("locations")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("locations")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithLocationRestriction(Data->HasField(ANSI_TO_TCHAR("locationRestriction")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("locationRestriction"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAnonymousIpDetection(Data->HasField(ANSI_TO_TCHAR("anonymousIpDetection")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("anonymousIpDetection"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAnonymousIpRestriction(Data->HasField(ANSI_TO_TCHAR("anonymousIpRestriction")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("anonymousIpRestriction"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithHostingProviderIpDetection(Data->HasField(ANSI_TO_TCHAR("hostingProviderIpDetection")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("hostingProviderIpDetection"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithHostingProviderIpRestriction(Data->HasField(ANSI_TO_TCHAR("hostingProviderIpRestriction")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("hostingProviderIpRestriction"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithReputationIpDetection(Data->HasField(ANSI_TO_TCHAR("reputationIpDetection")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("reputationIpDetection"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithReputationIpRestriction(Data->HasField(ANSI_TO_TCHAR("reputationIpRestriction")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("reputationIpRestriction"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithIpAddressesDetection(Data->HasField(ANSI_TO_TCHAR("ipAddressesDetection")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("ipAddressesDetection"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithIpAddresses(Data->HasField(ANSI_TO_TCHAR("ipAddresses")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("ipAddresses")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("ipAddresses")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("ipAddresses")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>())
            ->WithIpAddressRestriction(Data->HasField(ANSI_TO_TCHAR("ipAddressRestriction")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("ipAddressRestriction"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FBlockingPolicyModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PassServicesValue != nullptr && PassServicesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *PassServicesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("passServices", v);
        }
        if (DefaultRestrictionValue.IsSet())
        {
            JsonRootObject->SetStringField("defaultRestriction", DefaultRestrictionValue.GetValue());
        }
        if (LocationDetectionValue.IsSet())
        {
            JsonRootObject->SetStringField("locationDetection", LocationDetectionValue.GetValue());
        }
        if (LocationsValue != nullptr && LocationsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *LocationsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("locations", v);
        }
        if (LocationRestrictionValue.IsSet())
        {
            JsonRootObject->SetStringField("locationRestriction", LocationRestrictionValue.GetValue());
        }
        if (AnonymousIpDetectionValue.IsSet())
        {
            JsonRootObject->SetStringField("anonymousIpDetection", AnonymousIpDetectionValue.GetValue());
        }
        if (AnonymousIpRestrictionValue.IsSet())
        {
            JsonRootObject->SetStringField("anonymousIpRestriction", AnonymousIpRestrictionValue.GetValue());
        }
        if (HostingProviderIpDetectionValue.IsSet())
        {
            JsonRootObject->SetStringField("hostingProviderIpDetection", HostingProviderIpDetectionValue.GetValue());
        }
        if (HostingProviderIpRestrictionValue.IsSet())
        {
            JsonRootObject->SetStringField("hostingProviderIpRestriction", HostingProviderIpRestrictionValue.GetValue());
        }
        if (ReputationIpDetectionValue.IsSet())
        {
            JsonRootObject->SetStringField("reputationIpDetection", ReputationIpDetectionValue.GetValue());
        }
        if (ReputationIpRestrictionValue.IsSet())
        {
            JsonRootObject->SetStringField("reputationIpRestriction", ReputationIpRestrictionValue.GetValue());
        }
        if (IpAddressesDetectionValue.IsSet())
        {
            JsonRootObject->SetStringField("ipAddressesDetection", IpAddressesDetectionValue.GetValue());
        }
        if (IpAddressesValue != nullptr && IpAddressesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *IpAddressesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("ipAddresses", v);
        }
        if (IpAddressRestrictionValue.IsSet())
        {
            JsonRootObject->SetStringField("ipAddressRestriction", IpAddressRestrictionValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FBlockingPolicyModel::TypeName = "BlockingPolicyModel";
}