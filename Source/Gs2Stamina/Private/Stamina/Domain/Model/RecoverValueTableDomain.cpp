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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Stamina/Domain/Model/RecoverValueTable.h"
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FRecoverValueTableDomain::FRecoverValueTableDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RecoverValueTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Session)),
        NamespaceName(NamespaceName),
        RecoverValueTableName(RecoverValueTableName),
        ParentKey(Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "RecoverValueTable"
        ))
    {
    }

    FRecoverValueTableDomain::FRecoverValueTableDomain(
        const FRecoverValueTableDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FString FRecoverValueTableDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RecoverValueTableName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RecoverValueTableName.IsSet() ? *RecoverValueTableName : "null") + ":" +
            ChildType;
    }

    FString FRecoverValueTableDomain::CreateCacheKey(
        TOptional<FString> RecoverValueTableName
    )
    {
        return FString() +
            (RecoverValueTableName.IsSet() ? *RecoverValueTableName : "null");
    }

    FRecoverValueTableDomain::FModelTask::FModelTask(
        const TSharedPtr<FRecoverValueTableDomain> Self
    ): Self(Self)
    {

    }

    FRecoverValueTableDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverValueTable>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Stamina::Model::FRecoverValueTable> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Stamina::Model::FRecoverValueTable>(
            Self->ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverValueTableDomain::CreateCacheKey(
                Self->RecoverValueTableName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverValueTableDomain::FModelTask>> FRecoverValueTableDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRecoverValueTableDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

