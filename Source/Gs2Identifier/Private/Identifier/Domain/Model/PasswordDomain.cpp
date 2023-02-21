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

#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/AttachSecurityPolicy.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Identifier::Domain::Model
{

    FPasswordDomain::FPasswordDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> UserName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Session)),
        UserName(UserName),
        ParentKey(Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
            UserName,
            "Password"
        ))
    {
    }

    FPasswordDomain::FPasswordDomain(
        const FPasswordDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FPasswordDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FPasswordDomain> Self,
        const Request::FCreatePasswordRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->CreatePassword(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->UserName,
                    "Password"
                );
                const auto Key = Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
                );
                Self->Cache->Put<Gs2::Identifier::Model::FPassword>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FCreateTask>> FPasswordDomain::Create(
        Request::FCreatePasswordRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FGetTask::FGetTask(
        const TSharedPtr<FPasswordDomain> Self,
        const Request::FGetPasswordRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FPassword>> Result
    )
    {
        Request
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->GetPassword(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->UserName,
                    "Password"
                );
                const auto Key = Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
                );
                Self->Cache->Put<Gs2::Identifier::Model::FPassword>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FGetTask>> FPasswordDomain::Get(
        Request::FGetPasswordRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FPasswordDomain> Self,
        const Request::FDeletePasswordRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->DeletePassword(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->UserName,
                    "Password"
                );
                const auto Key = Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
                );
                Self->Cache->Delete<Gs2::Identifier::Model::FPassword>(ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FDeleteTask>> FPasswordDomain::Delete(
        Request::FDeletePasswordRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FPasswordDomain::CreateCacheParentKey(
        TOptional<FString> UserName,
        FString ChildType
    )
    {
        return FString() +
            (UserName.IsSet() ? *UserName : "null") + ":" +
            ChildType;
    }

    FString FPasswordDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FPasswordDomain::FModelTask::FModelTask(
        const TSharedPtr<FPasswordDomain> Self
    ): Self(Self)
    {

    }

    FPasswordDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FPassword>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Identifier::Model::FPassword>(
            Self->ParentKey,
            Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Identifier::Request::FGetPasswordRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "password")
                    {
                        Self->Cache->Delete<Gs2::Identifier::Model::FPassword>(
                            Self->ParentKey,
                            Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Identifier::Model::FPassword>(
                Self->ParentKey,
                Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FModelTask>> FPasswordDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPasswordDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

