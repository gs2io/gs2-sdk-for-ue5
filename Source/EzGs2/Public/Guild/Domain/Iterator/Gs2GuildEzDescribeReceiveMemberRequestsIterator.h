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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Guild/Domain/Model/GuildAccessToken.h"
#include "Guild/Model/Gs2GuildEzReceiveMemberRequest.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Guild::Domain::Iterator
{

	class EZGS2_API FEzDescribeReceiveMemberRequestsIterator :
        public TSharedFromThis<FEzDescribeReceiveMemberRequestsIterator>
    {
        Gs2::Guild::Domain::Iterator::FDescribeReceiveRequestsIteratorPtr It;
        Gs2::Guild::Domain::Model::FGuildAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;

	public:

        explicit FEzDescribeReceiveMemberRequestsIterator(
            Gs2::Guild::Domain::Model::FGuildAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        ) :
            It(
                Domain->ReceiveRequests(
                )
            ),
            Domain(Domain),
            GameSession(GameSession),
            Connection(Connection)
        {
        }

		FEzDescribeReceiveMemberRequestsIterator(
			const FEzDescribeReceiveMemberRequestsIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			GameSession(From.GameSession),
			Connection(From.Connection)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeReceiveMemberRequestsIterator;

			Gs2::Guild::Domain::Iterator::FDescribeReceiveRequestsIterator::FIterator DomainIterator;
			Gs2::UE5::Guild::Model::FEzReceiveMemberRequestPtr CurrentValue;
        	static Gs2::UE5::Guild::Model::FEzReceiveMemberRequestPtr ConvertCurrent(
        		Gs2::Guild::Domain::Iterator::FDescribeReceiveRequestsIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Guild::Model::FEzReceiveMemberRequest::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Guild::Domain::Iterator::FDescribeReceiveRequestsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeReceiveMemberRequestsIterator& Iterable
			) :
			    FIterator(Iterable.begin())
			{}

			FIterator(
			    const FIterator& Iterator
            ) :
                DomainIterator(Iterator.DomainIterator),
                CurrentValue(Iterator.CurrentValue)
            {}

			FIterator& operator*()
			{
				return *this;
			}

			const FIterator& operator*() const
			{
				return *this;
			}

			FIterator* operator->()
			{
				return this;
			}

			const FIterator* operator->() const
			{
				return this;
			}

			FIterator& operator++()
			{
				++DomainIterator;
				CurrentValue = ConvertCurrent(DomainIterator);
				return *this;
			}
            Gs2::UE5::Guild::Model::FEzReceiveMemberRequestPtr& Current()
            {
                return CurrentValue;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error()
            {
                return DomainIterator.Error();
            }

            bool IsError() const
            {
                return DomainIterator.IsError();
            }

            void Retry()
            {
                DomainIterator.Retry();
            }

			friend bool operator== (const FIterator& a, const FIterator& b)
			{
				return a.DomainIterator == b.DomainIterator;
			}
			friend bool operator!= (const FIterator& a, const FIterator& b)
			{
				return !operator==(a, b);
			}
		};

		FIterator OneBeforeBegin()
		{
			return FIterator(It->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(It->begin());
		}
		FIterator end()
		{
			return FIterator(It->end());
		}
    };
	typedef TSharedPtr<FEzDescribeReceiveMemberRequestsIterator> FEzDescribeReceiveMemberRequestsIteratorPtr;
}
