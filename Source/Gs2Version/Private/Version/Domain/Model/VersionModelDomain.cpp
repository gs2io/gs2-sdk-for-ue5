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

#include "Version/Domain/Model/VersionModel.h"
#include "Version/Domain/Model/Namespace.h"
#include "Version/Domain/Model/VersionModelMaster.h"
#include "Version/Domain/Model/VersionModel.h"
#include "Version/Domain/Model/AcceptVersion.h"
#include "Version/Domain/Model/AcceptVersionAccessToken.h"
#include "Version/Domain/Model/Checker.h"
#include "Version/Domain/Model/CheckerAccessToken.h"
#include "Version/Domain/Model/User.h"
#include "Version/Domain/Model/UserAccessToken.h"
#include "Version/Domain/Model/CurrentVersionMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Version::Domain::Model
{

    FVersionModelDomain::FVersionModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Version::Domain::FGs2VersionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> VersionName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Version::FGs2VersionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        VersionName(VersionName),
        ParentKey(Gs2::Version::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "VersionModel"
        ))
    {
    }

    FVersionModelDomain::FVersionModelDomain(
        const FVersionModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        VersionName(From.VersionName),
        ParentKey(From.ParentKey)
    {

    }

    FVersionModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FVersionModelDomain>& Self,
        const Request::FGetVersionModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FVersionModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FVersionModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Model::FVersionModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->GetVersionModel(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVersionModelDomain::FGetTask>> FVersionModelDomain::Get(
        Request::FGetVersionModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FVersionModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> VersionName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (VersionName.IsSet() ? *VersionName : "null") + ":" +
            ChildType;
    }

    FString FVersionModelDomain::CreateCacheKey(
        TOptional<FString> VersionName
    )
    {
        return FString("") +
            (VersionName.IsSet() ? *VersionName : "null");
    }

    FVersionModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FVersionModelDomain> Self
    ): Self(Self)
    {

    }

    FVersionModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVersionModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Model::FVersionModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Version::Model::FVersionModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Version::Model::FVersionModel>(
            Self->ParentKey,
            Gs2::Version::Domain::Model::FVersionModelDomain::CreateCacheKey(
                Self->VersionName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Version::Request::FGetVersionModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Version::Domain::Model::FVersionModelDomain::CreateCacheKey(
                    Self->VersionName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Version::Model::FVersionModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "versionModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Version::Model::FVersionModel>(
                Self->ParentKey,
                Gs2::Version::Domain::Model::FVersionModelDomain::CreateCacheKey(
                    Self->VersionName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVersionModelDomain::FModelTask>> FVersionModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FVersionModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FVersionModelDomain::Subscribe(
        TFunction<void(Gs2::Version::Model::FVersionModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Version::Model::FVersionModel::TypeName,
            ParentKey,
            Gs2::Version::Domain::Model::FVersionModelDomain::CreateCacheKey(
                VersionName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Version::Model::FVersionModel>(obj));
            }
        );
    }

    void FVersionModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Version::Model::FVersionModel::TypeName,
            ParentKey,
            Gs2::Version::Domain::Model::FVersionModelDomain::CreateCacheKey(
                VersionName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

