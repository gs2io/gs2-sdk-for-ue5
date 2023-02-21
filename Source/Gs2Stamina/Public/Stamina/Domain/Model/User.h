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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Stamina/Gs2Stamina.h"
#include "Stamina/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminaModelMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeMaxStaminaTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeRecoverIntervalTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeRecoverValueTableMastersIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminaModelsIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminasIterator.h"
#include "Stamina/Domain/Iterator/DescribeStaminasByUserIdIterator.h"

namespace Gs2::Stamina::Domain::Model
{
    class FNamespaceDomain;
    class FStaminaModelMasterDomain;
    class FMaxStaminaTableMasterDomain;
    class FRecoverIntervalTableMasterDomain;
    class FRecoverValueTableMasterDomain;
    class FCurrentStaminaMasterDomain;
    class FStaminaModelDomain;
    class FStaminaDomain;
    class FStaminaAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2STAMINA_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Stamina::FGs2StaminaRestClientPtr Client;

        public:
        TOptional<int64> OverflowValue;
        TOptional<FString> NextPageToken;
        TOptional<int64> GetOverflowValue() const
        {
            return OverflowValue;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        Gs2::Stamina::Domain::Iterator::FDescribeStaminasByUserIdIteratorPtr Staminas(
        ) const;

        TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain> Stamina(
            const FString StaminaName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
