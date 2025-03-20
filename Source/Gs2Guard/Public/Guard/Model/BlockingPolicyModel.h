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

namespace Gs2::Guard::Model
{
    class GS2GUARD_API FBlockingPolicyModel final : public FGs2Object, public TSharedFromThis<FBlockingPolicyModel>
    {
        TSharedPtr<TArray<FString>> PassServicesValue;
        TOptional<FString> DefaultRestrictionValue;
        TOptional<FString> LocationDetectionValue;
        TSharedPtr<TArray<FString>> LocationsValue;
        TOptional<FString> LocationRestrictionValue;
        TOptional<FString> AnonymousIpDetectionValue;
        TOptional<FString> AnonymousIpRestrictionValue;
        TOptional<FString> HostingProviderIpDetectionValue;
        TOptional<FString> HostingProviderIpRestrictionValue;
        TOptional<FString> ReputationIpDetectionValue;
        TOptional<FString> ReputationIpRestrictionValue;
        TOptional<FString> IpAddressesDetectionValue;
        TSharedPtr<TArray<FString>> IpAddressesValue;
        TOptional<FString> IpAddressRestrictionValue;

    public:
        FBlockingPolicyModel();
        FBlockingPolicyModel(
            const FBlockingPolicyModel& From
        );
        virtual ~FBlockingPolicyModel() override = default;

        TSharedPtr<FBlockingPolicyModel> WithPassServices(const TSharedPtr<TArray<FString>> PassServices);
        TSharedPtr<FBlockingPolicyModel> WithDefaultRestriction(const TOptional<FString> DefaultRestriction);
        TSharedPtr<FBlockingPolicyModel> WithLocationDetection(const TOptional<FString> LocationDetection);
        TSharedPtr<FBlockingPolicyModel> WithLocations(const TSharedPtr<TArray<FString>> Locations);
        TSharedPtr<FBlockingPolicyModel> WithLocationRestriction(const TOptional<FString> LocationRestriction);
        TSharedPtr<FBlockingPolicyModel> WithAnonymousIpDetection(const TOptional<FString> AnonymousIpDetection);
        TSharedPtr<FBlockingPolicyModel> WithAnonymousIpRestriction(const TOptional<FString> AnonymousIpRestriction);
        TSharedPtr<FBlockingPolicyModel> WithHostingProviderIpDetection(const TOptional<FString> HostingProviderIpDetection);
        TSharedPtr<FBlockingPolicyModel> WithHostingProviderIpRestriction(const TOptional<FString> HostingProviderIpRestriction);
        TSharedPtr<FBlockingPolicyModel> WithReputationIpDetection(const TOptional<FString> ReputationIpDetection);
        TSharedPtr<FBlockingPolicyModel> WithReputationIpRestriction(const TOptional<FString> ReputationIpRestriction);
        TSharedPtr<FBlockingPolicyModel> WithIpAddressesDetection(const TOptional<FString> IpAddressesDetection);
        TSharedPtr<FBlockingPolicyModel> WithIpAddresses(const TSharedPtr<TArray<FString>> IpAddresses);
        TSharedPtr<FBlockingPolicyModel> WithIpAddressRestriction(const TOptional<FString> IpAddressRestriction);

        TSharedPtr<TArray<FString>> GetPassServices() const;
        TOptional<FString> GetDefaultRestriction() const;
        TOptional<FString> GetLocationDetection() const;
        TSharedPtr<TArray<FString>> GetLocations() const;
        TOptional<FString> GetLocationRestriction() const;
        TOptional<FString> GetAnonymousIpDetection() const;
        TOptional<FString> GetAnonymousIpRestriction() const;
        TOptional<FString> GetHostingProviderIpDetection() const;
        TOptional<FString> GetHostingProviderIpRestriction() const;
        TOptional<FString> GetReputationIpDetection() const;
        TOptional<FString> GetReputationIpRestriction() const;
        TOptional<FString> GetIpAddressesDetection() const;
        TSharedPtr<TArray<FString>> GetIpAddresses() const;
        TOptional<FString> GetIpAddressRestriction() const;


        static TSharedPtr<FBlockingPolicyModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBlockingPolicyModel, ESPMode::ThreadSafe> FBlockingPolicyModelPtr;
}